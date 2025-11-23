#include "AST.h"
#include <stdexcept>
#include <vector>

// === Implement VariableExprAST::interpret() ===
double VariableExprAST::interpret() const {
  if (GlobalSymbolTable.count(Name)) {
    return GlobalSymbolTable.at(Name);
  }
  // ถ้าไม่พบตัวแปร ให้โยน Error
  throw std::runtime_error("Unknown variable name: " + Name);
}

// === Implement BinaryExprAST::interpret() ===
double BinaryExprAST::interpret() const {
  double L = LHS->interpret();
  double R = RHS->interpret();

  switch (Op) {
  case '+':
    return L + R;
  case '-':
    return L - R;
  case '*':
    return L * R;
  case '/':
    // เพิ่มการจัดการหารด้วยศูนย์ (ถ้าจำเป็น)
    if (R == 0.0)
      throw std::runtime_error("Division by zero");
    return L / R;

  default:
    throw std::runtime_error("Unknown binary operator: " + std::string(1, Op));
  }
}

// === Implement CallExprAST::interpret() ===
// สำหรับ Interpreter เบื้องต้น เราจะทำง่ายๆ โดยสมมติว่าฟังก์ชันถูกนิยามไว้
double CallExprAST::interpret() const {
  // 1. ค้นหาฟังก์ชันในตาราง
  auto It = FunctionTable.find(Callee);
  if (It == FunctionTable.end()) {
    throw std::runtime_error("Unknown function referenced: " + Callee);
  }

  // 2. ตรวจสอบจำนวน arguments
  const auto& ProtoArgs = It->second->getProto()->getArgs();
  if (ProtoArgs.size() != Args.size()) {
    throw std::runtime_error("Incorrect number of arguments passed to " + Callee);
  }

  // 3. คำนวณค่าของ arguments ที่ส่งเข้ามา
  std::vector<double> ArgVals;
  for (const auto& Arg : Args) {
    ArgVals.push_back(Arg->interpret());
  }

  // 4. เรียก interpret ที่ body ของฟังก์ชัน พร้อมส่งค่า arguments
  return It->second->interpretBody(ArgVals);
}

// === Implement FunctionAST::interpretBody() ===
double FunctionAST::interpretBody(const std::vector<double>& ArgVals) {
    // นี่คือส่วนที่สำคัญ: การสร้าง Local Scope สำหรับตัวแปร
    std::map<std::string, double> OldValues; // เก็บค่าเก่าของตัวแปร (ถ้ามี)
    const auto& ArgNames = Proto->getArgs();

    for (size_t i = 0; i < ArgNames.size(); ++i) {
        const std::string& ArgName = ArgNames[i];
        // ถ้ามีตัวแปรชื่อนี้อยู่แล้วใน Global, ให้เก็บค่าเก่าไว้ก่อน
        if (GlobalSymbolTable.count(ArgName)) {
            OldValues[ArgName] = GlobalSymbolTable[ArgName];
        }
        // ตั้งค่าตัวแปรใน GlobalSymbolTable ให้เป็นค่า argument ที่ได้รับมา
        GlobalSymbolTable[ArgName] = ArgVals[i];
    }

    double RetVal = Body->interpret(); // ประมวลผล Body ของฟังก์ชัน

    // คืนค่าตัวแปรใน GlobalSymbolTable ให้เป็นเหมือนเดิม
    for (const auto& Pair : OldValues) {
        GlobalSymbolTable[Pair.first] = Pair.second;
    }

    return RetVal;
}

// === Implement FunctionAST::interpret() ===
double FunctionAST::interpret() const {
    if (Body){
      return Body->interpret();
    }
    throw std::runtime_error("Cannot interpret function without a body.");
}
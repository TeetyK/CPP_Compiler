#include "AST.h"
#include <stdexcept>

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
  // การ Implement ที่สมบูรณ์จะต้องค้นหาฟังก์ชันในตารางฟังก์ชัน
  // สร้าง Environment ใหม่สำหรับ Arguments
  // แล้วเรียก Body->interpret() ของฟังก์ชันที่พบ
  throw std::runtime_error("Function calls are not fully implemented in the simple interpreter.");
}
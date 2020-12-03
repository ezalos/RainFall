char code[] = "bytecode will go here!";
int main(void)
{
  int (*func)();
  func = (int (*)()) code;
  (int)(*func)();
}
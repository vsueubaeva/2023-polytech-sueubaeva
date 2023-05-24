#include "src/ui.h"
#include "src/logic.h"

int main()
{
  calc::Logic logic;
  calc::UI ui(logic);

  ui.start();

  return 0;
}
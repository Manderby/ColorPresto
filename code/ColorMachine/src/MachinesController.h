
#import "main.h"


@interface MachinesController : NSObject {

  CMLColorMachine* cm; // current ColorMachine
  CMLColorMachine* sm; // current ScreenMachine

}

- (id)init;
- (void)recomputeScreenMachines;

- (void)resetCurrentMachine;
- (CMLColorMachine*)currentMachine;
- (CMLColorMachine*)currentScreenMachine;

@end

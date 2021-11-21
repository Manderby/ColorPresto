
#import "MachinesController.h"


@implementation MachinesController

- (id)init{
  cm = CMLcreateColorMachine();
//  CMLsetRadiometricComputation(cm, CMLTRUE);
  CMLsetMachineForColorClasses(cm);

  sm = NULL;
  [self recomputeScreenMachines];

  return [super init];
}


- (void)recomputeScreenMachines{
  if(sm){CMLreleaseColorMachine(sm);}

  sm = CMLcreateColorMachine();

  //sm->setRGBLUTSize(8);
  
  #if defined MAC_OS_X_VERSION_10_6
  
  
//    // the colorSpace method of the window is only available since 10.6
//    NSData* dataptr = [[[NSScreen mainScreen] colorSpace] ICCProfileData];
//    ICCProfile profile((Byte*)[dataptr bytes], [dataptr length]);
//
//    profile.printHeaderInfo();
//
//    cm->lockRecomputation();
//      cm->setWhitePointXYZ(profile.mediaWhitePoint);
//      Vector3<float> Yxy;
//      cm->XYZtoYxy(Yxy, profile.redMatrixColumn);
//      cm->setRedPrimary(Yxy[1], Yxy[2]);
//      cm->XYZtoYxy(Yxy, profile.greenMatrixColumn);
//      cm->setGreenPrimary(Yxy[1], Yxy[2]);
//      cm->XYZtoYxy(Yxy, profile.blueMatrixColumn);
//      cm->setBluePrimary(Yxy[1], Yxy[2]);
//    cm->releaseRecomputation();
    
  #endif

  
//  CGDirectDisplayID* displaylist;
//  CGDisplayCount displaycount = 0;
//  CGGetOnlineDisplayList(0, NULL, &displaycount);
//  displaylist = new CGDirectDisplayID[displaycount];
//  CGGetOnlineDisplayList(displaycount, displaylist, &displaycount);
//  for(CGDisplayCount d=0; d<displaycount; d++){
//    CGSize size = CGDisplayScreenSize(displaylist[d]);
//    bool isbuildin = CGDisplayIsBuiltin(displaylist[d]);
//    io_registry_entry_t ioport;
//    ioport = CGDisplayIOServicePort(displaylist[d]);
//    CFDataRef model;
//    model = (CFDataRef)IORegistryEntrySearchCFProperty(ioport,kIOServicePlane,CFSTR("model"), kCFAllocatorDefault,kIORegistryIterateRecursively | kIORegistryIterateParents);
//    String modelout((const char*)CFDataGetBytePtr(model), (MBSize)CFDataGetLength(model));
////    printf("build");
//    if(model)
//		CFRelease(model);
//
//  }
//  delete displaylist;
}

- (void)resetCurrentMachine{
  CMLreleaseColorMachine(cm);
  cm = CMLcreateColorMachine();
  CMLsetMachineForColorClasses(cm);
}

- (CMLColorMachine*)currentMachine{return cm;}
- (CMLColorMachine*)currentScreenMachine{return sm;}


@end

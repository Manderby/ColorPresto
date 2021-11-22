
#import "MachinesController.h"


@implementation MachinesController

- (id)init{
  cm = CMLcreateColorMachine();
//  CMLsetRadiometricComputation(cm, CML_TRUE);
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
//      Vector3<float> yxy;
//      cm->XYZtoYxy(yxy, profile.redMatrixColumn);
//      cm->setRedPrimary(yxy[1], yxy[2]);
//      cm->XYZtoYxy(yxy, profile.greenMatrixColumn);
//      cm->setGreenPrimary(yxy[1], yxy[2]);
//      cm->XYZtoYxy(yxy, profile.blueMatrixColumn);
//      cm->setBluePrimary(yxy[1], yxy[2]);
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


#import "main.h"


@interface AboutWindowController : NSWindowController {
  IBOutlet NSTextField* version;
  IBOutlet NSTextField* websitelink;
}
- (void)awakeFromNib;
- (void)showDialog;
//- (IBAction)pressDone:(NSButton*)sender;
- (IBAction)goToWebsite:(id)sender;

@end



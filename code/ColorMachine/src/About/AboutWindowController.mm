
#import "AboutWindowController.h"


@implementation AboutWindowController

- (void)awakeFromNib{
  NSString* versionstring = [[NSBundle mainBundle] objectForInfoDictionaryKey:@"CFBundleVersion"];
  [version setStringValue:[NSString stringWithFormat:@"%@%@", @"Version ", versionstring]];

  // both are needed, otherwise hyperlink won't accept mousedown
  [websitelink setAllowsEditingTextAttributes: YES];
  [websitelink setSelectable: YES];

  NSMutableAttributedString* attrString = [[NSMutableAttributedString alloc] initWithString: @"http://manderc.com"];
  NSRange range = NSMakeRange(0, [attrString length]);

  NSURL* url = [NSURL URLWithString:@"http://manderc.com"];
  [attrString beginEditing];
  [attrString addAttribute:NSLinkAttributeName value:[url absoluteString] range:range];
  [attrString addAttribute:NSUnderlineStyleAttributeName value:[NSNumber numberWithInt:NSUnderlineStyleSingle] range:range];
  [attrString addAttribute:NSForegroundColorAttributeName value:[NSColor blueColor] range:range];
  [attrString endEditing];

  [websitelink setAttributedStringValue: attrString];

  [attrString release];
}

- (void)showDialog{
  [[self window] makeKeyAndOrderFront:self];
}

//- (IBAction)pressDone:(NSButton*)sender{
//  [[self window] performClose:sender];
//}

- (IBAction)goToWebsite:(id)sender{
//  [websitebutton setTransparent:NO];
//  [[self window] performClose:sender];
  [[NSWorkspace sharedWorkspace] openURL:[NSURL URLWithString:@"http://manderc.com"]];
}

@end





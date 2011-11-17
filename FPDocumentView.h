/* FPDocumentView */

#import <Cocoa/Cocoa.h>
#import <PDFKit/PDFKit.h>

#define GRIDSIZE 15

@class FPGraphic;
@class MyDocument;

#define FPSelectionChangedNotification @"FPSelectionChangedNotification"

@interface FPDocumentView : NSView
{
    IBOutlet MyDocument *_doc;
    PDFDocument *_pdf_document;
    unsigned int _current_page;
    PDFDisplayBox _box;
    float _scale_factor;
    BOOL _draws_shadow;
    BOOL _inQuickMove;
    BOOL _is_printing;
	BOOL _has_gridOverlay;
    
    NSMutableArray *_overlayGraphics;
    NSMutableSet *_selectedGraphics;
    FPGraphic *_editingGraphic;
    
    // For zooming
    IBOutlet NSScrollView *_scrollView;
}

- (void)initMemberVariables;

- (void)setPDFDocument:(PDFDocument *)pdf_document;

- (void)zoomIn:(id)sender;
- (void)zoomOut:(id)sender;

- (void)nextPage;
- (void)previousPage;
- (void)scrollToPage:(unsigned int)page;

- (float)scaleFactor;

- (BOOL)shouldEnterQuickMove;
- (void)beginQuickMove:(id)unused;
- (void)endQuickMove:(id)unused;

- (NSSet *)selectedGraphics;
- (void)deleteSelectedGraphics;

- (BOOL)handleColorChange:(NSColor*)newColor;
- (NSColor*)defaultStrokeColor;

- (unsigned int)getViewingMidpointToPage:(unsigned int*)page pagePoint:(NSPoint*)pagePoint;
- (void)scrollToMidpointOnPage:(unsigned int)page point:(NSPoint)midPoint;

// place image
- (IBAction)placeImage:(id)sender;

// coordinate transforms
- (unsigned int)pageForPointFromEvent:(NSEvent *)theEvent;
- (unsigned int)pageForPoint:(NSPoint)point;
- (NSPoint)pagePointForPointFromEvent:(NSEvent *)theEvent
                                 page:(unsigned int)page;
- (NSRect)convertRect:(NSRect)rect toPage:(unsigned int)page;
- (NSRect)convertRect:(NSRect)rect fromPage:(unsigned int)page;
- (NSPoint)convertPoint:(NSPoint)point toPage:(unsigned int)page;
- (NSPoint)convertPoint:(NSPoint)point fromPage:(unsigned int)page;

// printing
- (FPDocumentView *)printableCopy;
- (NSRect)rectForPage:(int)page; // indexed from 1, not 0


// opening and saving
- (NSArray *)archivalOverlayGraphics;
- (void)setOverlayGraphicsFromArray:(NSArray *)arr;

// font
- (NSFont *)currentFont;

// private
- (NSAffineTransform *)transformForPage:(unsigned int)page;

//refresh for grid overlay pref
- (void) refreshPrefs;
@end

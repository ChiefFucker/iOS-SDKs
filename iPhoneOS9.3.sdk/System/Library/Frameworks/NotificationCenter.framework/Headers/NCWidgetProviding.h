//
//  NCWidgetProviding.h
//  NotificationCenter
//
//  Copyright (c) 2014 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

// If the widget has local state that can be loaded quickly, it should do so before returning from ‘viewWillAppear:’.
// Otherwise, the widget should ensure that the state and layout of its view when returning from 'viewWillAppear:’ will match that of the last time it returned from 'viewWillDisappear:', transitioning smoothly to the new data later when it arrives.”

// While the Notification Center ultimately controls the layout of its children, widgets can request a change in height.
// Widgets with heights defined by constraints will be automatically adjusted (within limits).
// Widgets using explicit layout can request a new height (that may, or may not, be adjusted or honored at all) by changing the value of their ‘preferredContentSize’.
// Should either form of request result in a height change, the widget will be messaged with ‘viewWillTransitionToSize:withTransitionCoordinator:’ and, if the transition is animated, passed a transition coordinator.
// If the transition coordinator argument is not 'nil', and the widget has additional animations it wishes to run in concert with the height change, it can specify them and/or a completion block by messaging the coordinator with 'animateAlongsideTransition:completion:'.

typedef NS_ENUM(NSUInteger, NCUpdateResult) {
    NCUpdateResultNewData,
    NCUpdateResultNoData,
    NCUpdateResultFailed
} NS_ENUM_AVAILABLE_IOS(8_0);

// 'NCWidgetProviding' is an optional protocol for further customizing aspects of the provided content. 

NS_ASSUME_NONNULL_BEGIN
@protocol NCWidgetProviding <NSObject>

@optional

// If implemented, the system will call at opportune times for the widget to update its state, both when the Notification Center is visible as well as in the background.
// An implementation is required to enable background updates.
// It's expected that the widget will perform the work to update asynchronously and off the main thread as much as possible.
// Widgets should call the argument block when the work is complete, passing the appropriate 'NCUpdateResult'.
// Widgets should NOT block returning from 'viewWillAppear:' on the results of this operation.
// Instead, widgets should load cached state in 'viewWillAppear:' in order to match the state of the view from the last 'viewWillDisappear:', then transition smoothly to the new data when it arrives.
- (void)widgetPerformUpdateWithCompletionHandler:(void (^)(NCUpdateResult result))completionHandler;

// Widgets wishing to customize the default margin insets can return their preferred values.
// Widgets that choose not to implement this method will receive the default margin insets.
- (UIEdgeInsets)widgetMarginInsetsForProposedMarginInsets:(UIEdgeInsets)defaultMarginInsets;

@end

@interface UIVibrancyEffect (NotificationCenter)

+ (UIVibrancyEffect *)notificationCenterVibrancyEffect;

@end
NS_ASSUME_NONNULL_END

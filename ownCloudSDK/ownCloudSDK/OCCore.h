//
//  OCCore.h
//  ownCloudSDK
//
//  Created by Felix Schwarz on 05.02.18.
//  Copyright © 2018 ownCloud GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "OCBookmark.h"
#import "OCVault.h"
#import "OCQuery.h"
#import "OCItem.h"
#import "OCActivity.h"
#import "OCConnection.h"
#import "OCShare.h"

@class OCCore;
@class OCItem;

typedef void(^OCCoreActionResultHandler)(NSError *error, OCCore *core, OCItem *item);
typedef void(^OCCoreActionShareHandler)(NSError *error, OCCore *core, OCItem *item, OCShare *share);
typedef void(^OCCoreCompletionHandler)(NSError *error);

@protocol OCCoreDelegate <NSObject>

- (void)core:(OCCore *)core handleError:(NSError *)error;

@end

@interface OCCore : NSObject <OCEventHandler>

@property(readonly) OCBookmark *bookmark; //!< Bookmark identifying the server this core manages.

@property(readonly) OCVault *vault; //!< Vault managing storage and database access for this core.
@property(readonly) OCConnection *connection; //!< Connection used by the core to make requests to the server.

@property(weak) id <OCCoreDelegate> delegate;

#pragma mark - Init
- (instancetype)initWithBookmark:(OCBookmark *)bookmark NS_DESIGNATED_INITIALIZER;

#pragma mark - Query
- (void)startQuery:(OCQuery *)query;
- (void)stopQuery:(OCQuery *)query;

#pragma mark - Commands
- (OCActivity *)createFolderNamed:(NSString *)newFolderName atPath:(OCPath)path options:(NSDictionary *)options resultHandler:(OCCoreActionResultHandler)resultHandler;
- (OCActivity *)createEmptyFileNamed:(NSString *)newFileName atPath:(OCPath)path options:(NSDictionary *)options resultHandler:(OCCoreActionResultHandler)resultHandler;

- (OCActivity *)renameItem:(OCItem *)item to:(NSString *)newFileName resultHandler:(OCCoreActionResultHandler)resultHandler;
- (OCActivity *)moveItem:(OCItem *)item to:(OCPath)newParentDirectoryPath resultHandler:(OCCoreActionResultHandler)resultHandler;
- (OCActivity *)copyItem:(OCItem *)item to:(OCPath)newParentDirectoryPath options:(NSDictionary *)options resultHandler:(OCCoreActionResultHandler)resultHandler;

- (OCActivity *)deleteItem:(OCItem *)item resultHandler:(OCCoreActionResultHandler)resultHandler;

- (OCActivity *)uploadFileAtURL:(NSURL *)url to:(OCPath)newParentDirectoryPath resultHandler:(OCCoreActionResultHandler)resultHandler;
- (OCActivity *)downloadItem:(OCItem *)item to:(OCPath)newParentDirectoryPath resultHandler:(OCCoreActionResultHandler)resultHandler;

- (OCActivity *)retrieveThumbnailFor:(OCItem *)item resultHandler:(OCCoreActionResultHandler)resultHandler;

- (OCActivity *)shareItem:(OCItem *)item options:(OCShareOptions)options resultHandler:(OCCoreActionShareHandler)resultHandler;

- (OCActivity *)requestAvailableOfflineCapabilityForItem:(OCItem *)item completionHandler:(OCCoreCompletionHandler)completionHandler;
- (OCActivity *)terminateAvailableOfflineCapabilityForItem:(OCItem *)item completionHandler:(OCCoreCompletionHandler)completionHandler;

- (OCActivity *)synchronizeWithServer;

@end
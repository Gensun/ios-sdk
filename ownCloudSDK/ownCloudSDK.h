//
//  ownCloudSDK.h
//  ownCloudSDK
//
//  Created by Felix Schwarz on 05.02.18.
//  Copyright © 2018 ownCloud GmbH. All rights reserved.
//

/*
 * Copyright (C) 2018, ownCloud GmbH.
 *
 * This code is covered by the GNU Public License Version 3.
 *
 * For distribution utilizing Apple mechanisms please see https://owncloud.org/contribute/iOS-license-exception/
 * You should have received a copy of this license along with this program. If not, see <http://www.gnu.org/licenses/gpl-3.0.en.html>.
 *
 */

#import <Foundation/Foundation.h>

//! Project version number for ownCloudSDK.
FOUNDATION_EXPORT double ownCloudSDKVersionNumber;

//! Project version string for ownCloudSDK.
FOUNDATION_EXPORT const unsigned char ownCloudSDKVersionString[];

// In this header, you should import all the public headers of your framework using statements like #import <ownCloudSDK/PublicHeader.h>

#import <ownCloudSDK/OCTypes.h>
#import <ownCloudSDK/OCMacros.h>
#import <ownCloudSDK/NSError+OCError.h>

#import <ownCloudSDK/OCAppIdentity.h>

#import <ownCloudSDK/OCClassSettings.h>
#import <ownCloudSDK/NSObject+OCClassSettings.h>
#import <ownCloudSDK/OCClassSettingsFlatSource.h>
#import <ownCloudSDK/OCClassSettingsFlatSourceManagedConfiguration.h>
#import <ownCloudSDK/OCClassSettingsFlatSourcePropertyList.h>

#import <ownCloudSDK/OCCore.h>
#import <ownCloudSDK/NSProgress+OCEvent.h>

#import <ownCloudSDK/OCBookmark.h>

#import <ownCloudSDK/OCAuthenticationMethod.h>
#import <ownCloudSDK/OCAuthenticationMethodBasicAuth.h>
#import <ownCloudSDK/OCAuthenticationMethodOAuth2.h>

#import <ownCloudSDK/OCConnection.h>
#import <ownCloudSDK/OCConnectionRequest.h>
#import <ownCloudSDK/OCConnectionDAVRequest.h>
#import <ownCloudSDK/OCConnectionQueue.h>

#import <ownCloudSDK/OCEvent.h>
#import <ownCloudSDK/OCEventTarget.h>

#import <ownCloudSDK/OCVault.h>
#import <ownCloudSDK/OCDatabase.h>
#import <ownCloudSDK/OCSQLiteDB.h>
#import <ownCloudSDK/OCSQLiteQuery.h>
#import <ownCloudSDK/OCSQLiteTransaction.h>
#import <ownCloudSDK/OCSQLiteResultSet.h>

#import <ownCloudSDK/OCQuery.h>
#import <ownCloudSDK/OCQueryFilter.h>
#import <ownCloudSDK/OCQueryChangeSet.h>

#import <ownCloudSDK/OCItem.h>

#import <ownCloudSDK/OCShare.h>
#import <ownCloudSDK/OCUser.h>

#import <ownCloudSDK/OCSyncRecord.h>

#import <ownCloudSDK/NSURL+OCURLNormalization.h>
#import <ownCloudSDK/NSURL+OCURLQueryParameterExtensions.h>

#import <ownCloudSDK/OCXMLNode.h>
#import <ownCloudSDK/OCXMLParser.h>
#import <ownCloudSDK/OCXMLParserNode.h>

#import <ownCloudSDK/OCReachabilityMonitor.h>

#import <ownCloudSDK/OCLogger.h>

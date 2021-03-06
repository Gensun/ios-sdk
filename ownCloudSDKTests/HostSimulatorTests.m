//
//  HostSimulatorTests.m
//  ownCloudSDKTests
//
//  Created by Felix Schwarz on 22.03.18.
//  Copyright © 2018 ownCloud GmbH. All rights reserved.
//

#import <XCTest/XCTest.h>

#import <ownCloudSDK/ownCloudSDK.h>
#import "OCHostSimulator.h"

@interface HostSimulatorTests : XCTestCase
{
	OCHostSimulator *hostSimulator;
}

@end

@implementation HostSimulatorTests

- (void)setUp {
	[super setUp];
	// Put setup code here. This method is called before the invocation of each test method in the class.

	hostSimulator = [[OCHostSimulator alloc] init];
}

- (void)tearDown {
	// Put teardown code here. This method is called after the invocation of each test method in the class.
	[super tearDown];
}

- (void)_runPreparationTestsForURL:(NSURL *)url completionHandler:(void(^)(NSURL *url, OCBookmark *bookmark, OCConnectionIssue *issue, NSArray <OCAuthenticationMethodIdentifier> *supportedMethods, NSArray <OCAuthenticationMethodIdentifier> *preferredAuthenticationMethods))completionHandler
{
	XCTestExpectation *expectAnswer = [self expectationWithDescription:@"Received reply"];

	OCBookmark *bookmark = [OCBookmark bookmarkForURL:url];

	OCConnection *connection;

	connection = [[OCConnection alloc] initWithBookmark:bookmark];
	connection.hostSimulator = hostSimulator;

	[connection prepareForSetupWithOptions:nil completionHandler:^(OCConnectionIssue *issue,  NSURL *suggestedURL, NSArray<OCAuthenticationMethodIdentifier> *supportedMethods, NSArray<OCAuthenticationMethodIdentifier> *preferredAuthenticationMethods) {
		NSLog(@"Issues: %@", issue.issues);
		NSLog(@"SuggestedURL: %@", suggestedURL);
		NSLog(@"Supported authentication methods: %@ - Preferred authentication methods: %@", supportedMethods, preferredAuthenticationMethods);

		completionHandler(url, bookmark, issue, supportedMethods, preferredAuthenticationMethods);

		[expectAnswer fulfill];
	}];

	[self waitForExpectationsWithTimeout:60 handler:nil];
}

- (void)testSimulatorMissingCertificate
{
	[self _runPreparationTestsForURL:[NSURL URLWithString:@"https://demo.owncloud.org/"] completionHandler:^(NSURL *url, OCBookmark *bookmark, OCConnectionIssue *issue, NSArray<OCAuthenticationMethodIdentifier> *supportedMethods, NSArray<OCAuthenticationMethodIdentifier> *preferredAuthenticationMethods) {
		XCTAssert(issue.issues.count==1, @"1 issue found");

		XCTAssert((issue.issues[0].type == OCConnectionIssueTypeError), @"Issue is error issue");
		XCTAssert((issue.issues[0].level == OCConnectionIssueLevelError), @"Issue level is error");

		XCTAssert((issue.issues[0].error.code == OCErrorCertificateMissing), @"Error is that certificate is missing");
	}];
}

- (void)testSimulatorSimulatedNotFoundResponses
{
	[self _runPreparationTestsForURL:[NSURL URLWithString:@"http://demo.owncloud.org/"] completionHandler:^(NSURL *url, OCBookmark *bookmark, OCConnectionIssue *issue, NSArray<OCAuthenticationMethodIdentifier> *supportedMethods, NSArray<OCAuthenticationMethodIdentifier> *preferredAuthenticationMethods) {
		XCTAssert(issue.issues.count==1, @"1 issue found");

		XCTAssert((issue.issues[0].type == OCConnectionIssueTypeError), @"Issue is error issue");
		XCTAssert((issue.issues[0].level == OCConnectionIssueLevelError), @"Issue level is error");

		XCTAssert((issue.issues[0].error.code == OCErrorServerDetectionFailed), @"Error is that server couldn't be detected (thanks to simulated 404 responses)");
	}];
}

- (void)testSimulatorInjectResponsesIntoRealConnection
{
	// Do not answer with 404 responses for all unimplemented URLs, but rather let the request through to the real network
	hostSimulator.unroutableRequestHandler = nil;

	hostSimulator.responseByPath = @{

		// Mock response to "/remote.php/dav/files" so that demo.owncloud.org appears to also offer OAuth2 authentication (which it at the time of writing doesn't)
		@"/remote.php/dav/files" :
			[OCHostSimulatorResponse responseWithURL:nil
						statusCode:OCHTTPStatusCodeOK
						headers:@{
							@"Www-Authenticate" : @"Bearer realm=\"\", Basic realm=\"\""
						}
						contentType:@"application/xml"
						body:@""]

	};

	[self _runPreparationTestsForURL:[NSURL URLWithString:@"https://demo.owncloud.org/"] completionHandler:^(NSURL *url, OCBookmark *bookmark, OCConnectionIssue *issue, NSArray<OCAuthenticationMethodIdentifier> *supportedMethods, NSArray<OCAuthenticationMethodIdentifier> *preferredAuthenticationMethods) {
		XCTAssert(issue.issues.count==1, @"1 issue found");

		XCTAssert((issue.issues[0].type == OCConnectionIssueTypeCertificate), @"Issue is certificate issue");
		XCTAssert((issue.issues[0].level == OCConnectionIssueLevelInformal), @"Issue level is informal");

		XCTAssert((preferredAuthenticationMethods.count == 2), @"2 preferred authentication methods");
		XCTAssert([preferredAuthenticationMethods[0] isEqual:OCAuthenticationMethodOAuth2Identifier], @"OAuth2 is first detected authentication method");
		XCTAssert([preferredAuthenticationMethods[1] isEqual:OCAuthenticationMethodBasicAuthIdentifier], @"Basic Auth is second detected authentication method");

		[issue approve];

		XCTAssert (([bookmark.url isEqual:url]) && (bookmark.originURL==nil), @"Bookmark has expected values");
	}];
}

@end


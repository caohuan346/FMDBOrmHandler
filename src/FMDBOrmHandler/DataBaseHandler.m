//
//  DBCenter.m
//  XMPPBaseProject
//
//  Created by hc on 13-9-11.
//  Copyright (c) 2013年 hc. All rights reserved.
//

#import "DataBaseHandler.h"

#import "AppDelegate.h"

@implementation DataBaseHandler

#pragma mark - singleton
SYNTHESIZE_SINGLETON_FOR_CLASS(DataBaseHandler)

- (id)init{
	if ((self = [super init]))
    {
		self.state = FALSE;
        
        NSString *filePath = @"/Users/zc/Desktop/db.sqlite";
        
        self.fmdbQueue=[[FMDatabaseQueue alloc] initWithPath:filePath];
        self.database = [[FMDatabase alloc]initWithPath:filePath];
        
        self.queue=[[NSOperationQueue alloc] init];
        self.queue.maxConcurrentOperationCount=1;
	}
	return self;
}

- (BOOL)createDb {
    
    if ([self.database open]) {
        [self.database setShouldCacheStatements:YES];
        NSLog(@"Open success db !");
    }else {
        NSLog(@"Failed to open db!");
    }
    
    //User
//    BOOL tUserFlag = [[BaseDao sharedInstance] createTableWithDBModel:[[User alloc] init]];

	return NO;
}

#pragma mark Customized:General

/*
//local db update handle
- (void)handleDbUpdate {
    
	NSString *allConfigFilePath = [PathService pathForAllConfigFile];
    
	if ([[NSFileManager defaultManager] fileExistsAtPath:allConfigFilePath]) {
		NSMutableDictionary *allConfigDictionary = [[NSMutableDictionary alloc]
							   initWithContentsOfFile:allConfigFilePath];
        //sandbox中数据库版本
		NSString *lastDBVersion = [allConfigDictionary objectForKey:@"dbVersion"];
        
        //如果sandbox中存在数据库版本大于等于目标版本，不需要更新
		if ([lastDBVersion compare:KNextDBVersion] != NSOrderedAscending) {
			NSLog(@"save db ver, do nothing.");
		}
        //change db
        else{
            
        }
	}

}
*/

@end

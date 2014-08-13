//
//  DBCenter.h
//  FMDBOrmHandler
//
//  Created by hc on 14-07-05.
//  Copyright (c) 2014年 hc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "FMDatabase.h"
#import "FMDatabaseAdditions.h"
#import "FMDatabaseQueue.h"
#import "BaseDao.h"

@class BaseDao;
@interface DataBaseHandler : NSObject
{
    
}

@property (nonatomic, assign) BOOL state;

@property (nonatomic, strong) FMDatabase *database;

@property (nonatomic, strong) FMDatabaseQueue  *fmdbQueue;

@property (nonatomic, strong) NSOperationQueue  *queue;

//singleton
SYNTHESIZE_SINGLETON_FOR_HEADER(DataBaseHandler)

//
- (BOOL)createDb;

- (void)handleDbUpdate;

@end

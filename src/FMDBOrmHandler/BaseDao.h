//
//  BaseDBManager.h
//  XMPPBaseProject
//
//  Created by hc on 14-07-05.
//  Copyright (c) 2014年 hc. All rights reserved.
//

#import <Foundation/Foundation.h>

#define DEPRECATED(_version) __attribute__((deprecated))

#define SYNTHESIZE_SINGLETON_FOR_HEADER(className) \
\
+ (className *) sharedInstance;


#define SYNTHESIZE_SINGLETON_FOR_CLASS(className) \
\
+ (className *)sharedInstance { \
static className *sharedInstance = nil; \
static dispatch_once_t onceToken; \
dispatch_once(&onceToken, ^{ \
sharedInstance = [[self alloc] init]; \
}); \
return sharedInstance; \
}

#import "NSObject+Property.h"
#import "DBModelProtocol.h"

#define CHComparisonMarkEQ @"="     //Equal
#define CHComparisonMarkGT @">"     //Greater Than
#define CHComparisonMarkGE @">="    //Greater than or equal to
#define CHComparisonMarkLT @"<"     //Less than
#define CHComparisonMarkLE @"<="    //Less than or equal to
#define CHComparisonMarkNE @"<>"    //Not Equal

#define CHComparisonMarkLike @"like"  //模糊查询
#define CHOrderMarkDesc @"desc"       //降序
#define CHOrderMarkAsc  @"asc"        //升序

@class DataBaseHandler,ConditionBean;
@interface BaseDao : NSObject

//singleton
SYNTHESIZE_SINGLETON_FOR_HEADER(BaseDao)

#pragma mark - drop or create table
/**
 *	删除数据库已经存在的表
 *
 *	@param	tableName 表名
 *
 *	@return	删除flag
 */
- (BOOL)dropExistsTable:(NSString*)tableName;

/**
 *	删除数据库全部表
 */
- (BOOL)dropAllTable;

/**
 *	查询数据库是否存在表
 *
 *	@param	tablename	表名
 *
 *	@return	查询flag
 */
- (BOOL)isExistsTable:(NSString *)tablename;

/**
 *	sql执行
 *
 *	@param	sql	待执行的sql
 */
- (void)executeByQueue:(NSString *)sql;

#pragma mark - CRUD common : for every table in sqlite
//如下的删除和更新的条件都是等值条件：即where子句中都是 “字段名=值” 的形式

/**
 *	根据条件字典删除记录
 *
 *	@param	tableName	表名
 *	@param	conditionDic	条件字典
 *
 *	@return	删除flag
 */
- (BOOL)deleteRecord:(NSString*) tableName withConditionDic:(NSDictionary*) conditionDic;

/**
 *	根据待修改的信息字典和条件字典修改对应的记录
 *
 *	@param	tableName	表名
 *	@param	modifyDic	待修改的信息字典
 *	@param	conditionDic	条件字典
 *
 *	@return	更新flag
 */
- (BOOL)updateTable:(NSString*) tableName withModifyValueDic:(NSDictionary*)modifyDic withConditionDic:(NSDictionary*) conditionDic;

#pragma mark - CRUD common2 : for every table in sqlite
//下面的四个方法为数据库通用方法，所有表都能用使用
//其中查询、更新、删除可以是任意条件：如where子句中可能有的 >=,<,+,<>,like等，针对查询还提供排序
//注意使用的conditionBeanDic是 value为ConditionBean,key为条件字段的字典

/**
 *	根据信息字典插入记录
 *
 *	@param	tableName	表名
 *	@param	dictionary	字典信息
 *
 *	@return	插入flag
 */
- (BOOL)insertTable:(NSString*) tableName withDictionary:(NSDictionary*) dictionary;

/**
 *	根据字典数组批量插入表
 *
 *	@param	tableName	表名
 *	@param	dataArray	字典信息数组
 *
 *	@return	插入flag
 */
- (BOOL)insertTableInBatchMode:(NSString*) tableName withDictionaryArray:(NSArray*) dataArray;

/**
 *	根据ConditionBean删除对应的记录
 *
 *	@param	tableName	表名
 *	@param	conditionBeanArray	ConditionBean数组
 *
 *	@return	删除标记
 */
- (BOOL)deleteRecord:(NSString *)tableName withConditionBeanArray:(NSArray *)conditionBeanArray;

/**
 *	根据ConditionBean对象数组查询对应的字典结果集
 *
 *	@param	tableName	表名
 *	@param	conditionBeanArray	ConditionBean数组
 *
 *	@return	字典结果集合
 */
- (NSArray *)query2DictionaryArray:(NSString*) tableName withConditionBeanArray:(NSArray *)conditionBeanArray;

/**
 *	根据sql查询出对应的字典结果集
 *
 *	@param	sql	查询sql
 *
 *	@return	字典结果集
 */
- (NSArray *)query2DictionaryArrayWithSql:(NSString *)sql;

/**
 *	根据待修改的信息实体，ConditionBean对象数组更新相关记录
 *
 *	@param	tableName	表名
 *	@param	modifiedDic
 *	@param	conditionBeanArray	ConditionBean对象数组
 *
 *	@return	更新flag
 */
- (BOOL)updateRecord:(NSString *)tableName withModifiedDic:(NSDictionary *)modifiedDic withConditionBeanArray:(NSArray *)conditionBeanArray;

#pragma mark - CRUD3
//下面的所有方法为数据库通用方法，根据实体反射实现，
//注意不是所有的表都能用，必须是通过实体建立的表，保证实体表的的属性对应表的字段，名称一致，属性一致

#pragma mark - create table

/**
 *	建表
 *
 *	@param	model	dbmodel
 *
 *	@return	success flag
 */
- (BOOL)createTableWithDBModel:(NSObject<DBModelProtocol> *) model;

#pragma mark - insert

/**
 *	根据字典信息插入数据
 *
 *	@param	model	dbmodel
 *	@param	dict	数据字典
 */
- (BOOL)insertDBModel:(NSObject<DBModelProtocol> *) model dict:(NSDictionary *)dict;

/**
 *	插入实体记录
 *
 *	@param	model	数据对象
 *
 *	@return	success flag
 */
- (BOOL)insertDBModel:(NSObject<DBModelProtocol> *) model;

/**
 *	批量插入实体
 *
 *	@param	modelArray	实体对象数组
 *
 *	@return	success flag
 */
- (BOOL)insertDBModelArray:(NSArray *)modelArray;

#pragma mark - delete

/**
 *	删除记录
 *
 *	@param	model	对应表中的一条记录
 *	@param	conditonBean	单一条件bean
 *
 *	@return	delete flag
 */
- (BOOL)deleteDbModel:(NSObject<DBModelProtocol> *) model withConditionBean:(ConditionBean *)conditonBean;

/**
 *	删除记录
 *
 *	@param	model 对应表中的一条记录
 *
 *	@return	success flag
 */
- (BOOL)deleteDbModel:(NSObject<DBModelProtocol> *) model withConditionBeanArray:(NSArray *)conditionBeanArray;

#pragma mark - query: for object which is implement DBModelProtocol

/**
 *	根据ConditionBean数组查询对应对象数组
 *
 *	@param	model	model
 *	@param	conditionBeanArray	ConditionBean数组
 *
 *	@return	结果对象数组
 */
- (NSArray *)query2ObjectArrayWithDBModel:(NSObject<DBModelProtocol> *)model withConditionBeanArray:(NSArray *)conditionBeanArray;

/**
 *	根据条件对象信息查询对应对象数组
 *
 *	@param	conditionModel	条件对象
 *
 *	@return	结果集
 */
- (NSArray *)query2ObjectArrayWithConditionObject:(NSObject<DBModelProtocol> *)conditionModel DEPRECATED(2_01);

/**
 *	根据条件对象信息查询对应字典信息数组
 *
 *	@param	conditionModel	条件对象
 *
 *	@return	字典结果集
 */
- (NSArray *)query2DictionaryArrayWithConditionObject:(NSObject<DBModelProtocol> *)conditionModel;

#pragma mark - update

/**
 *	根据值对象和条件字典更新对应记录:各字段的各种条件，如大于、不等于，like...
 *
 *	@param	model	更新记录
 *	@param	conditionBeanArray	条件bean数组
 *
 *	@return	success flag
 */
- (BOOL)updateDBModel:(NSObject<DBModelProtocol> *)model withConditionBeanArray:(NSArray *)conditionBeanArray;

/**
 *	更新记录，以主键作为查询条件
 *
 *	@param	model	目标信息实体对象
 *
 *	@return	success flag
 */
- (BOOL)updateDBModel:(NSObject<DBModelProtocol> *)model;

- (void)updateDBModel:(NSObject<DBModelProtocol> *)model withConditionBeanArray:(NSArray *)conditionBeanArray callBack:(void(^)(BOOL))block;

@end


//
//  ConditionBean.h
//  XMPPBaseProject
//
//  Created by hc on 14-07-05.
//  Copyright (c) 2013年 hc. All rights reserved.
//
@interface ConditionBean : NSObject

@property(nonatomic,copy)   NSString    *filedName;         //字段名称
@property(nonatomic,strong) NSObject    *filedValue;        //字段值
@property(nonatomic,copy)   NSString    *comparisonMark;    //条件比较标记
@property(nonatomic,copy)   NSString    *orderMark;         //排序标记
@property(nonatomic,assign) NSInteger   limitSize;          //分页每页条数
@property(nonatomic,assign) NSInteger   offset;             //当前offset

/**
 *	条件、排序
 *
 *	@param	fieldName	字段名
 *	@param	comparisonMark	比较符号
 *	@param	filedValue	字段值
 *	@param	orderMark	排序条件
 *
 *	@return	ConditionBean
 */
+(id)conditionWhereAndOrderBeanWithField:(NSString *)fieldName compare:(NSString *)comparisonMark withValue:(NSObject *)filedValue inOrder:(NSString *)orderMark;

/**
 *	条件bean
 *
 *	@param	fieldName	字段名
 *	@param	comparisonMark	比较符号
 *	@param	filedValue	字段值
 *
 *	@return	ConditionBean
 */
+(id)conditionWhereBeanWithField:(NSString *)fieldName compare:(NSString *)comparisonMark withValue:(NSObject *)filedValue;

/**
 *	排序bean
 *
 *	@param	fieldName	字段名
 *	@param	orderMark	排序条件
 *
 *	@return	ConditionBean
 */
+(id)conditionOrderBeanWithField:(NSString *)fieldName inOrder:(NSString *)orderMark;

/**
 *	分页查询bean
 *
 *	@param	size	查询每页条数
 *	@param	offset	查询offset
 *
 *	@return ConditionBean
 */
+(id)conditionLimitBeanWithSize:(NSInteger)size offset:(NSInteger)offset;

@end

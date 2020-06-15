/*
 * Copyright 2009-2016 the original author or authors.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/**
 * @file    spk_general_client_define.h
 *
 * 適用於一般情況下的通用客戶端環境
 *
 * @version 1.0 2016/8/10
 * @since   2016/8/10
 */


#ifndef _SPK_GENERAL_CLIENT_ENV_DEFINE_H
#define _SPK_GENERAL_CLIENT_ENV_DEFINE_H


#include    <sutil/net/spk_global_packet.h>
#include    <sutil/net/spk_data_buffer_define.h>
#include    <sutil/net/spk_socket_base_define.h>


#ifdef __cplusplus
extern "C" {
#endif


/* ===================================================================
 * 常量定義
 * =================================================================== */

/** 預設的心跳間隔(秒) */
#define GENERAL_CLI_DEFAULT_HEARTBEAT_INTERVAL      (30)
/** 最小的心跳間隔(秒) */
#define GENERAL_CLI_MIN_HEARTBEAT_INTERVAL          (5)
/** 最大的心跳間隔(秒) */
#define GENERAL_CLI_MAX_HEARTBEAT_INTERVAL          (3600)

/** 預設的UDP連線的心跳間隔(秒) */
#define GENERAL_CLI_DEFAULT_UDP_HEARTBEAT_INTERVAL  (30)
/** 最大的UDP連線的心跳間隔/最大空閒時間(秒) */
#define GENERAL_CLI_MAX_UDP_ALIVE_INTERVAL          (180)
/** 預設的超時時間(毫秒) */
#define GENERAL_CLI_DEFAULT_TIMEOUT_MS              SPK_DEFAULT_SO_TIMEOUT_MS

/** 最大的單個應答訊息大小 */
#define GENERAL_CLI_MAX_RSPMSG_SIZE                 (4 * 1024 * 1024)
/** 預設的TCP接收快取大小 */
#define GENERAL_CLI_DEFAULT_TCP_RECVBUF_SIZE        (8 * 1024 * 1024)
/** 預設的UDP接收快取大小 */
#define GENERAL_CLI_DEFAULT_UDP_RECVBUF_SIZE        (4 * 1024 * 1024)
/** 最小的接收快取剩餘可用空間大小 */
#define GENERAL_CLI_MIN_RECVBUF_SURPLUS_SIZE        (128 * 1024)
/** 預設的編解碼快取大小 */
#define GENERAL_CLI_DEFAULT_CODEC_BUF_SIZE          (512 * 1024)

/** 最大的主機編號 */
#define GENERAL_CLI_MAX_HOST_NUM                    (9)
/** 可連線的最大遠端伺服器數量 */
#define GENERAL_CLI_MAX_REMOTE_CNT                  (8)
/** 連線通道組的最大連線數量 */
#define GENERAL_CLI_MAX_CHANNEL_GROUP_SIZE          (64)

/** 會話資訊中用於儲存自定義資料的擴充套件空間大小 */
#define GENERAL_CLI_MAX_SESSION_EXTDATA_SIZE        (128)

/** 客戶端名稱最大長度 */
#define GENERAL_CLI_MAX_NAME_LEN                    (32)
/** 客戶端說明最大長度 */
#define GENERAL_CLI_MAX_DESC_LEN                    (32)
/** 密碼最大長度 */
#define GENERAL_CLI_MAX_PWD_LEN                     (40)
/** 傳送方/接收方程式碼字串的最大長度 */
#define GENERAL_CLI_MAX_COMP_ID_LEN                 (32)
/* -------------------------           */


/* ===================================================================
 * 常量定義（列舉型別定義）
 * =================================================================== */

/**
 * 伺服器叢集的叢集型別
 */
typedef enum _eGeneralClientClusterType {
    GENERAL_CLI_CLUSTER_UNDEFINED           = 0,    /**< 未指定 (使用預設的叢集型別) */
    GENERAL_CLI_CLUSTER_REPLICA_SET         = 1,    /**< 基於複製集的高可用叢集 */
    GENERAL_CLI_CLUSTER_PEER_NODES          = 2,    /**< 基於對等節點的伺服器叢集 */
    __MAX_GENERAL_CLI_CLUSTER_TYPE
} eGeneralClientClusterTypeT;
/* -------------------------           */


/**
 * 加密型別
 */
typedef enum _eGeneralClientEncryptType {
    GENERAL_CLI_ENCRYPT_NONE                = 0,    /**< 加密型別-無 */
    GENERAL_CLI_ENCRYPT_MD5                 = 0x01, /**< 加密型別-MD5 */
    GENERAL_CLI_ENCRYPT_SHA                 = 0x02, /**< 加密型別-SHA */
    GENERAL_CLI_ENCRYPT_DES                 = 0x10, /**< 加密型別-DES */
    GENERAL_CLI_ENCRYPT_AES                 = 0x20, /**< 加密型別-AES */
    GENERAL_CLI_ENCRYPT_RSA                 = 0x40, /**< 加密型別-RSA */

    __GENERAL_CLI_ENCRYPT_MASK_DIGESTED     = 0x0F, /**< 加密型別-訊息摘要類演算法掩碼 */
    __GENERAL_CLI_ENCRYPT_MASK_ENCRYPTED    = 0xF0  /**< 加密型別-加密類演算法掩碼 */
} eGeneralClientEncryptTypeT;
/* -------------------------           */


/* ===================================================================
 * 結構體定義
 * =================================================================== */

/**
 * 通用的客戶端會話資訊（連線通道資訊）定義
 */
typedef struct _SGeneralClientChannel {
    union {
        /** Socket描述符 */
        SPK_SOCKET      socketFd;
        /** 按64位對齊的填充域 */
        uint64          __socket_fd_filler;
    };

    int32               heartBtInt;             /**< 心跳間隔，單位為秒 (允許預先賦值) */
    int32               testReqInt;             /**< 測試請求間隔，單位為秒 */
    uint8               protocolType;           /**< 協議型別 (Binary, JSON等) (允許預先賦值) */
    uint8               remoteSetNum;           /**< 對端伺服器的叢集號 */
    uint8               remoteHostNum;          /**< 已連線上的對端伺服器的主機編號 */
    uint8               remoteIsLeader;         /**< 對端伺服器是否是'主節點' */
    uint8               leaderHostNum;          /**< '主節點'的主機編號 */
    uint8               __filler1[3];           /**< 按64位對齊填充域 */

    struct _SDataBufferVar
                        __codecBuf;             /**< 編解碼快取 */
    struct _SDataBufferVar
                        __recvBuf;              /**< 接收快取 */
    char                *__pDataStartPoint;     /**< 資料起始位置指標 */
    void                *__customPtr;           /**< 可以由應用層自定義使用的指標變數 */
    int32               __reavedSize;           /**< 已接收到但尚未處理的資料長度 */
    int32               __customFlag;           /**< 可以由應用層自定義使用的整型變數 */
    int64               __totalInMsgSize;       /**< 累計接收到的未壓縮資料大小 */
    int64               __totalCompressedSize;  /**< 累計接收到的已壓縮資料大小 */
    int64               __totalDecompressSize;  /**< 解壓縮後的資料總大小 */

    uint64              firstInMsgSeq;          /**< 已接收到的起始入向訊息序號 */
    uint64              lastInMsgSeq;           /**< 實際已接收到的入向訊息序號 (對應於登入應答訊息的 lastOutMsgSeq) */
    uint64              nextInMsgSeq;           /**< 期望的入向訊息序號 */
    STimevalT           lastRecvTime;           /**< 接收時間 */

    SSocketChannelInfoT channel;                /**< 連線通道資訊 */
    uint64              nextOutMsgSeq;          /**< 出向訊息序號 */
    uint64              lastOutMsgSeq;          /**< 實際已傳送的出向訊息序號 (對應於登入應答訊息的 lastInMsgSeq) */
    STimevalT           lastSendTime;           /**< 傳送時間 */

    /** 傳送方程式碼 */
    char                senderCompId[GENERAL_CLI_MAX_COMP_ID_LEN];
    /** 接收方程式碼 */
    char                targetCompId[GENERAL_CLI_MAX_COMP_ID_LEN];

    int32               __magicNumber;          /**< 標識會話結構是否已經正確初始化過 */
    int32               __magicSize;            /**< 標識會話資訊的結構體大小 */

    uint8               __channelType;          /**< 通道型別 */
    int8                __clEnvId;              /**< 客戶端環境號 */
    uint8               __groupFlag;            /**< 通道組標誌 */
    uint8               __protocolHints;        /**< 協議約定資訊 */
    uint8               __filler[4];            /**< 按64位對齊填充域 */

    /** 保留給伺服器或API內部使用的，用於儲存自定義資料的擴充套件空間 */
    union {
        char            buf[GENERAL_CLI_MAX_SESSION_EXTDATA_SIZE];
        int8            i8[GENERAL_CLI_MAX_SESSION_EXTDATA_SIZE];
        uint8           u8[GENERAL_CLI_MAX_SESSION_EXTDATA_SIZE];
        int16           i16[GENERAL_CLI_MAX_SESSION_EXTDATA_SIZE / 2];
        uint16          u16[GENERAL_CLI_MAX_SESSION_EXTDATA_SIZE / 2];
        int32           i32[GENERAL_CLI_MAX_SESSION_EXTDATA_SIZE / 4];
        uint32          u32[GENERAL_CLI_MAX_SESSION_EXTDATA_SIZE / 4];
        int64           i64[GENERAL_CLI_MAX_SESSION_EXTDATA_SIZE / 8];
        uint64          u64[GENERAL_CLI_MAX_SESSION_EXTDATA_SIZE / 8];
        void            *ptr[GENERAL_CLI_MAX_SESSION_EXTDATA_SIZE / 8];
        char            __padding[GENERAL_CLI_MAX_SESSION_EXTDATA_SIZE
                                  + SPK_CACHE_LINE_SIZE];
    } __reserveData;

    /** 可以由應用層自定義使用的，用於儲存自定義資料的擴充套件空間 */
    union {
        char            buf[GENERAL_CLI_MAX_SESSION_EXTDATA_SIZE];
        int8            i8[GENERAL_CLI_MAX_SESSION_EXTDATA_SIZE];
        uint8           u8[GENERAL_CLI_MAX_SESSION_EXTDATA_SIZE];
        int16           i16[GENERAL_CLI_MAX_SESSION_EXTDATA_SIZE / 2];
        uint16          u16[GENERAL_CLI_MAX_SESSION_EXTDATA_SIZE / 2];
        int32           i32[GENERAL_CLI_MAX_SESSION_EXTDATA_SIZE / 4];
        uint32          u32[GENERAL_CLI_MAX_SESSION_EXTDATA_SIZE / 4];
        int64           i64[GENERAL_CLI_MAX_SESSION_EXTDATA_SIZE / 8];
        uint64          u64[GENERAL_CLI_MAX_SESSION_EXTDATA_SIZE / 8];
        void            *ptr[GENERAL_CLI_MAX_SESSION_EXTDATA_SIZE / 8];
    } __extData;
} SGeneralClientChannelT;


/* 結構體的初始化值定義 */
#define NULLOBJ_GENERAL_CLIENT_CHANNEL          \
        {0}, 0, 0, \
        0, 0, 0, 0, 0, {0}, \
        {NULLOBJ_SPK_DATA_BUFFER}, \
        {NULLOBJ_SPK_DATA_BUFFER}, \
        0, 0, 0, 0, 0, 0, 0, \
        0, 0, 0, {0, 0}, \
        {NULLOBJ_SOCKET_CHANNEL_INFO}, \
        0, 0, {0, 0}, \
        {0}, {0}, \
        0, 0, \
        0, 0, 0, 0, {0}, \
        {{0}}, {{0}}
/* -------------------------           */


/**
 * 通用的連線通道組定義（多個連線通道的集合）
 */
typedef struct _SGeneralClientChannelGroup {
    /** 連線通道數量 */
    int32               channelCount;
    /** 可以由應用層自定義使用的整型變數 */
    int32               __customFlag;
    /** 連線通道資訊列表 */
    SGeneralClientChannelT
                        *channelList[GENERAL_CLI_MAX_CHANNEL_GROUP_SIZE];

    /** 最大的連線描述符 (僅供系統內部使用) */
    int32               __maxFd;
    /** 最大的連線描述符集合大小 (僅供系統內部使用) */
    int16               __maxFdCnt;
    /** 通道組標誌 (僅供系統內部使用) */
    uint8               __groupFlag;
    /** 按64位對齊的填充域 */
    uint8               __filler;
    /** 連線描述符集合 (僅供系統內部使用) */
    union {
        SPollfdT        __fdArray[GENERAL_CLI_MAX_CHANNEL_GROUP_SIZE];
        fd_set          __fdSet;
    };
} SGeneralClientChannelGroupT;


/* 結構體的初始化值定義 */
#define NULLOBJ_GENERAL_CLIENT_CHANNEL_GROUP    \
        0, 0, {0}, \
        0, 0, 0, 0, \
        {{{0, 0, 0}}}
/* -------------------------           */


/**
 * Socket URI地址資訊
 */
typedef struct _SGeneralClientAddrInfo {
    /** 地址資訊 */
    char                uri[SPK_MAX_URI_LEN];
    /** 接收方程式碼 */
    char                targetCompId[GENERAL_CLI_MAX_COMP_ID_LEN];
    /** 使用者名稱 */
    char                username[GENERAL_CLI_MAX_NAME_LEN];
    /** 密碼 */
    char                password[GENERAL_CLI_MAX_PWD_LEN];

    /** 主機編號 */
    uint8               hostNum;
    /** 按64位對齊的填充域 */
    uint8               __filler[7];
} SGeneralClientAddrInfoT;


/* 結構體初始化值定義 */
#define NULLOBJ_GENERAL_CLIENT_ADDR_INFO        \
        {0}, {0}, {0}, {0}, \
        0, {0}
/* -------------------------           */


/**
 * 遠端主機配置資訊
 */
typedef struct _SGeneralClientRemoteCfg {
    int32               addrCnt;                /**< 伺服器地址的數量 */
    int32               heartBtInt;             /**< 心跳間隔,單位為秒 */
    uint8               clusterType;            /**< 伺服器叢集的叢集型別 (0:對等節點, 1:複製集) */
    int8                clEnvId;                /**< 客戶端環境號 */
    uint8               __filler[6];            /**< 按64位對齊的填充域 */

    /** 傳送方程式碼 */
    char                senderCompId[GENERAL_CLI_MAX_COMP_ID_LEN];
    /** 接收方程式碼 */
    char                targetCompId[GENERAL_CLI_MAX_COMP_ID_LEN];
    /** 使用者名稱 */
    char                username[GENERAL_CLI_MAX_NAME_LEN];
    /** 密碼 */
    char                password[GENERAL_CLI_MAX_PWD_LEN];

    /** 伺服器地址列表 */
    SGeneralClientAddrInfoT     addrList[GENERAL_CLI_MAX_REMOTE_CNT];

    /** 套介面選項配置 */
    SSocketOptionConfigT        socketOpt;
} SGeneralClientRemoteCfgT;


/* 結構體的初始化值定義 */
#define NULLOBJ_GENERAL_CLIENT_REMOTE_CFG       \
        0, 0, 0, 0, {0}, \
        {0}, {0}, {0}, {0}, \
        {{NULLOBJ_GENERAL_CLIENT_ADDR_INFO}}, \
        {NULLOBJ_SOCKET_OPTION_CONFIG}
/* -------------------------           */


/* ===================================================================
 * 輔助的巨集定義
 * =================================================================== */

/**
 * 返回伺服器地址所對應的接收方程式碼配置
 *
 * @param   P_REMOTE_CFG    主機配置資訊的結構體指標 @see SGeneralClientRemoteCfgT
 * @param   ADDR_INDEX      伺服器地址的順序號
 * @return  接收方程式碼
 */
#define _SGeneralClient_GetTargetCompId(P_REMOTE_CFG, ADDR_INDEX)   \
        ( (P_REMOTE_CFG)->addrList[(ADDR_INDEX)].targetCompId[0] != '\0' \
                ? (P_REMOTE_CFG)->addrList[(ADDR_INDEX)].targetCompId \
                        : (P_REMOTE_CFG)->targetCompId )


/**
 * 返回伺服器地址所對應的使用者名稱配置
 *
 * @param   P_REMOTE_CFG    主機配置資訊的結構體指標 @see SGeneralClientRemoteCfgT
 * @param   ADDR_INDEX      伺服器地址的順序號
 * @return  使用者名稱
 */
#define _SGeneralClient_GetUsername(P_REMOTE_CFG, ADDR_INDEX)       \
        ( (P_REMOTE_CFG)->addrList[(ADDR_INDEX)].username[0] != '\0' \
                ? (P_REMOTE_CFG)->addrList[(ADDR_INDEX)].username \
                        : (P_REMOTE_CFG)->username )


/**
 * 返回伺服器地址所對應的密碼配置
 *
 * @param   P_REMOTE_CFG    主機配置資訊的結構體指標 @see SGeneralClientRemoteCfgT
 * @param   ADDR_INDEX      伺服器地址的順序號
 * @return  密碼
 */
#define _SGeneralClient_GetPassword(P_REMOTE_CFG, ADDR_INDEX)       \
        ( (P_REMOTE_CFG)->addrList[(ADDR_INDEX)].password[0] != '\0' \
                ? (P_REMOTE_CFG)->addrList[(ADDR_INDEX)].password \
                        : (P_REMOTE_CFG)->password )
/* -------------------------           */


#ifdef __cplusplus
}
#endif

#endif  /* _SPK_GENERAL_CLIENT_ENV_DEFINE_H */

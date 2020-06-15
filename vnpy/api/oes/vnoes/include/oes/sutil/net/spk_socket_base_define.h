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
 * @file    spk_socket_base_define.h
 *
 * Socket公共巨集定義等標頭檔案
 *
 * @version 1.0 2013/7/18
 * @since   2004/3/26
 */


#ifndef _SPK_SOCKET_BASE_DEFINE_H
#define _SPK_SOCKET_BASE_DEFINE_H


#include    <sutil/types.h>


#ifdef __cplusplus
extern "C" {
#endif


/* ===================================================================
 * 平臺相關的預編譯巨集設定
 * =================================================================== */

#ifndef TCP_KEEPIDLE
#   if defined (__APPLE__)
#       define  TCP_KEEPIDLE            TCP_KEEPALIVE
#   endif
#endif
/* -------------------------           */


/* ===================================================================
 * 常量定義
 * =================================================================== */

/** IP字串的最大長度 */
#define SPK_MAX_IP_LEN                  (16)
/** IPv6字串的最大長度 */
#define SPK_MAX_IPV6_LEN                (40)
/** URI最大長度 */
#define SPK_MAX_URI_LEN                 (128)
/** 通訊協議型別名稱的最大長度 */
#define SPK_MAX_PROTOCOL_NAME_LEN       (32)
/** 通訊協議型別描述的最大長度 */
#define SPK_MAX_PROTOCOL_MEMO_LEN       (64)
/** MAC地址字串的最大長度 */
#define SPK_MAX_MAC_LEN                 (20)
/** MAC地址字串的最大長度(按64位對齊的長度) */
#define SPK_MAX_MAC_ALGIN_LEN           (24)
/** 裝置序列號字串的最大長度 */
#define SPK_MAX_DRIVER_ID_LEN           (24)

/** 最大同時連線請求數 */
#if defined(__MINGW__) || defined(__CYGWIN__) || defined(__WINDOWS__)
#   define  SPK_MAX_SO_BACKLOG          (128)
#else
#   define  SPK_MAX_SO_BACKLOG          (SOMAXCONN)
#endif

/** 預設的最大同時連線請求數 */
#define SPK_DEFAULT_SO_BACKLOG          SPK_MAX_SO_BACKLOG
/** 預設的接收快取大小（單位: K） */
#define SPK_DEFAULT_SO_RCVBUF           (1024)
/** 預設的傳送快取大小（單位: K） */
#define SPK_DEFAULT_SO_SNDBUF           (1024)
/** 預設的SO_NODELAY取值 */
#define SPK_DEFAULT_TCP_NODELAY         (1)
/** 預設的SO_REUSEADDR取值 */
#define SPK_DEFAULT_SO_REUSEADDR        (1)

/** 預設的連線操作的超時時間 (毫秒) */
#define SPK_DEFAULT_CONN_TIMEOUT_MS     (10000)
/** 最大的連線操作的超時時間 (毫秒) */
#define SPK_MAX_CONN_TIMEOUT_MS         (60000)

/** 預設的SOCKET超時時間 (毫秒) */
#ifndef SPK_DEFAULT_SO_TIMEOUT_MS
#   define  SPK_DEFAULT_SO_TIMEOUT_MS   (10000)
#endif
/** 常用的較短的SOCKET超時時間 (毫秒) */
#define SPK_SHORT_SO_TIMEOUT_MS         (5000)
/** 常用的最短的SOCKET超時時間 (毫秒) */
#define SPK_SHORTEST_SO_TIMEOUT_MS      (1000)
/** 常用的較長的SOCKET超時時間 (毫秒) */
#define SPK_LONG_SO_TIMEOUT_MS          (30000)
/** 常用的最長的SOCKET超時時間 (毫秒) */
#define SPK_LONGEST_SO_TIMEOUT_MS       (60000)

/** 預設的SO_KEEPALIVE取值 */
#define SPK_DEFAULT_SO_KEEPALIVE        (1)
/** 預設的TCP_KEEPIDLE取值 */
#define SPK_DEFAULT_TCP_KEEPIDLE        (300)
/** 預設的TCP_KEEPINTVL取值 */
#define SPK_DEFAULT_TCP_KEEPINTVL       (30)
/** 預設的TCP_KEEPCNT取值 */
#define SPK_DEFAULT_TCP_KEEPCNT         (9)
/* -------------------------           */


/* ===================================================================
 * 常量定義（列舉型別定義）
 * =================================================================== */

/**
 * 通訊協議型別
 */
typedef enum _eSSocketProtocolType {
    SPK_SOCKET_PROTOCOL_TCP             = 0,    /**< 通訊協議型別 - TCP */
    SPK_SOCKET_PROTOCOL_IPC             = 1,    /**< 通訊協議型別 - IPC (Unix Domain Socket) */
    SPK_SOCKET_PROTOCOL_UDP_UCAST       = 2,    /**< 通訊協議型別 - UDP-Unicast */
    SPK_SOCKET_PROTOCOL_UDP_MCAST       = 3,    /**< 通訊協議型別 - UDP-Multicast */
    SPK_SOCKET_PROTOCOL_PGM             = 4,    /**< 通訊協議型別 - PGM */
    SPK_SOCKET_PROTOCOL_EPGM            = 5,    /**< 通訊協議型別 - EPGM */
    __MAX_SPK_SOCKET_PROTOCOL
} eSSocketProtocolTypeT;
/* -------------------------           */


/* ===================================================================
 * 結構體定義
 * =================================================================== */

/**
 * Socket URI地址資訊
 */
typedef struct _SSocketUriInfo {
    /** 地址資訊 */
    char                uri[SPK_MAX_URI_LEN];
} SSocketUriInfoT;


/* 結構體初始化值定義 */
#define NULLOBJ_SOCKET_URI_INFO             \
        {0}
/* -------------------------           */


/**
 * Socket IP/Port 地址資訊
 */
typedef struct _SSocketIpPortInfo {
    /** 埠號 */
    int32               port;
    /** IP地址 */
    char                ip[SPK_MAX_IP_LEN + 4];
} SSocketIpPortInfoT;


/* 結構體初始化值定義 */
#define NULLOBJ_SOCKET_IP_PORT_INFO         \
        0, {0}
/* -------------------------           */


/**
 * Socket 連線通道資訊
 */
typedef struct _SSocketChannelInfo {
    union {
        /** Socket描述符 */
        SPK_SOCKET      socketFd;
        /** 按64位對齊的填充域 */
        uint64          __socket_fd_filler;
    };

    /** 套接字埠號 */
    int32               remotePort;

    /**
     * 通訊協議型別
     * @see eSSocketProtocolTypeT
     */
    uint8               protocolType;

    /** 是否使用網路位元組序 (TRUE 網路位元組序；FALSE 本機位元組序) */
    uint8               _isNetByteOrder;

    /** 連線是否已破裂 (用於內部處理) */
    uint8               _isBroken;

    /** 標示非同步傳送執行緒的連線是否已破裂 (用於內部處理) */
    uint8               _isSendBroken;

    /** 套接字地址或DomainSocket的路徑地址 (僅用於顯示) */
    char                remoteAddr[SPK_MAX_URI_LEN];
} SSocketChannelInfoT;


/* 結構體初始化值定義 */
#define NULLOBJ_SOCKET_CHANNEL_INFO         \
        {0}, 0, \
        0, 0, 0, 0, {0}
/* -------------------------           */


/**
 * 套介面選項配置
 */
typedef struct _SSocketOptionConfig {
    /** socket SO_RCVBUF size (KB) */
    int32               soRcvbuf;
    /** socket SO_SNDBUF size (KB) */
    int32               soSndbuf;

    /** socket TCP_NODELAY option, 0 or 1 */
    int8                tcpNodelay;
    /** socket TCP_QUICKACK option, 0 or 1 */
    int8                quickAck;

    /** mutilcast TTL number */
    int8                mcastTtlNum;
    /** disable mutilcast loopback, 0 or 1 */
    int8                mcastLoopbackDisabled;

    /** BACKLOG size for listen */
    uint16              soBacklog;
    /** 連線操作(connect)的超時時間 (毫秒) */
    uint16              connTimeoutMs;

    /** socket TCP_KEEPIDLE option, 超時時間(秒) */
    int16               keepIdle;
    /** socket TCP_KEEPINTVL option, 間隔時間(秒) */
    int16               keepIntvl;
    /** socket SO_KEEPALIVE option, 0 or 1 */
    int8                keepalive;
    /** socket TCP_KEEPCNT option, 嘗試次數 */
    int8                keepCnt;
    /** 按64位對齊的填充域 */
    int8                __filler[6];

    /** 本地繫結的埠地址 (適用於傳送端) */
    int32               localSendingPort;
    /** 本地繫結的網路裝置介面的IP地址 (適用於傳送端) */
    char                localSendingIp[SPK_MAX_IP_LEN + 4];
    /** 用於組播接收和傳送的特定網路裝置介面的IP地址 */
    char                mcastInterfaceIp[SPK_MAX_IP_LEN + 4];
} SSocketOptionConfigT;


/* 結構體初始化值定義 */
#define NULLOBJ_SOCKET_OPTION_CONFIG        \
        SPK_DEFAULT_SO_RCVBUF, SPK_DEFAULT_SO_SNDBUF, \
        SPK_DEFAULT_TCP_NODELAY, 0, \
        0, 0, \
        SPK_MAX_SO_BACKLOG, SPK_DEFAULT_CONN_TIMEOUT_MS, \
        SPK_DEFAULT_TCP_KEEPIDLE, SPK_DEFAULT_TCP_KEEPINTVL, \
        SPK_DEFAULT_SO_KEEPALIVE, SPK_DEFAULT_TCP_KEEPCNT, \
        {0}, \
        0, {0}, {0}
/* -------------------------           */


#ifdef __cplusplus
}
#endif

#endif  /* _SPK_SOCKET_BASE_DEFINE_H */

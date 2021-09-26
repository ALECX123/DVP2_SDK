/** @mainpage ����
*
*/
#ifndef __DVPCAMERA_H__
#define __DVPCAMERA_H__

#include <windows.h>

#ifndef __cplusplus
#define bool unsigned char
#define false (0)
#define true  (1)
#endif
#ifndef dvp2api
#ifndef __cplusplus
#define dvp2api extern     __declspec(dllimport)
#else
#define dvp2api extern "C" __declspec(dllimport)
#endif
#endif

/** @defgroup __DVP2_ENUM__ ö����
*@{
*/
/** @brief ͼ���ʽ*/
typedef enum dvpImageFormat
{
    /** @brief �ڰ�ͼ�� */
    FORMAT_MONO = 0,

    /** @brief BGGRͼ�� */
    FORMAT_BAYER_BG = 1,

    /** @brief GBRGͼ�� */
    FORMAT_BAYER_GB = 2,

    /** @brief GRBGͼ�� */
    FORMAT_BAYER_GR = 3,

    /** @brief RGGBͼ�� */
    FORMAT_BAYER_RG = 4,

    /** @brief RGB��ͨ��24����ͼ�� */
    FORMAT_BGR24 = 10,

    /** @brief RGBA��ͨ��32����ͼ�� */
    FORMAT_BGR32 = 11,

    /** @brief YUV411 */
    FORMAT_YUV_411 = 20,

    /** @brief YUV422 */
    FORMAT_YUV_422 = 21,

} dvpImageFormat;


/** @brief ��������ʽ*/
typedef enum dvpStreamFormat
{
    /** @brief 8λͼ�� */
    S_RAW8 = 0,

    /** @brief 10λͼ�� */
    S_RAW10 = 1,

    /** @brief 12λͼ�� */
    S_RAW12 = 2,

    /** @brief 14λͼ�� */
    S_RAW14 = 3,

    /** @brief 16λͼ�� */
    S_RAW16 = 4,

    /** @brief RGB��ͨ��24����ͼ�� */
    S_BGR24 = 10,

    /** @brief YUV411 */
    S_YCBCR_411 = 20,

    /** @brief YUV422 */
    S_YCBCR_422 = 21,

    /** @brief YUV444 */
    S_YCBCR_444 = 22,

    /** @brief 8λ�Ҷ�ͼ�� */
    S_MONO8 = 30,

    /** @brief 10λ�Ҷ�ͼ�� */
    S_MONO10 = 31,

    /** @brief 12λ�Ҷ�ͼ�� */
    S_MONO12 = 32,

    /** @brief 14λ�Ҷ�ͼ�� */
    S_MONO14 = 33,

    /** @brief 16λ�Ҷ�ͼ�� */
    S_MONO16 = 34,

} dvpStreamFormat;


/** @brief ͼ��λ��*/
typedef enum dvpBits
{
    /** @brief 8�������� */
    BITS_8 = 0,

    /** @brief 10�������� */
    BITS_10 = 1,

    /** @brief 12�������� */
    BITS_12 = 2,

    /** @brief 14�������� */
    BITS_14 = 3,

    /** @brief 16�������� */
    BITS_16 = 4,

} dvpBits;


/** @brief �Զ��ع�ģʽ*/
typedef enum dvpAeMode
{
    /** @brief �Զ��ع⣬�Զ�����ͬʱ�������ع����� */
    AE_MODE_AE_AG = 0,

    /** @brief �Զ��ع⣬�Զ�����ͬʱ�������������� */
    AE_MODE_AG_AE = 1,

    /** @brief �Զ��ع� */
    AE_MODE_AE_ONLY = 2,

    /** @brief �Զ����� */
    AE_MODE_AG_ONLY = 3,

} dvpAeMode;


/** @brief �Զ��ع����*/
typedef enum dvpAeOperation
{
    /** @brief ���ܹر� */
    AE_OP_OFF = 0,

    /** @brief ����һ�� */
    AE_OP_ONCE = 1,

    /** @brief �������� */
    AE_OP_CONTINUOUS = 2,

} dvpAeOperation;


/** @brief �Զ���ƽ�����*/
typedef enum dvpAwbOperation
{
    /** @brief ���ܹر� */
    AWB_OP_OFF = 0,

    /** @brief ����һ�� */
    AWB_OP_ONCE = 1,

    /** @brief �������� */
    AWB_OP_CONTINUOUS = 2,

} dvpAwbOperation;


/** @brief �ƹ�Ƶ��*/
typedef enum dvpAntiFlick
{
    /** @brief ��ֹ����Ƶ�� */
    ANTIFLICK_DISABLE = 0,

    /** @brief ����50hzƵ�� */
    ANTIFLICK_50HZ = 1,

    /** @brief ����60hzƵ�� */
    ANTIFLICK_60HZ = 2,

} dvpAntiFlick;


/** @brief ����������*/
typedef enum dvpSensorType
{
    /** @brief CMOSͼ�񴫸��� */
    SENSOR_TYPE_CMOS = 0,

    /** @brief CCDͼ�񴫸��� */
    SENSOR_TYPE_CCD = 1,

} dvpSensorType;


/** @brief ��������������*/
typedef enum dvpSensorPixel
{
    /** @brief �ڰ����� */
    SENSOR_PIXEL_MONO = 0,

    /** @brief RGGB��ɫ���� */
    SENSOR_PIXEL_BAYER_RG = 1,

    /** @brief GBRG��ɫ���� */
    SENSOR_PIXEL_BAYER_GB = 2,

    /** @brief GRBG��ɫ���� */
    SENSOR_PIXEL_BAYER_GR = 3,

    /** @brief BGGR��ɫ���� */
    SENSOR_PIXEL_BAYER_BG = 4,

} dvpSensorPixel;


/** @brief ��Ƶ���ص��¼�*/
typedef enum dvpStreamEvent
{
    /** @brief ͼ��ﵽ�� */
    STREAM_EVENT_ARRIVED = 0,

    /** @brief ͼ��У���� */
    STREAM_EVENT_CORRECTED = 1,

    /** @brief ͼ����� */
    STREAM_EVENT_PROCESSED = 2,

} dvpStreamEvent;


/** @brief ���������ź�����*/
typedef enum dvpTriggerInputType
{
    /** @brief ��������ر� */
    TRIGGER_IN_OFF = 0,

    /** @brief �½��ش��� */
    TRIGGER_NEG_EDGE = 1,

    /** @brief �͵�ƽ���� */
    TRIGGER_LOW_LEVEL = 2,

    /** @brief �����ش��� */
    TRIGGER_POS_EDGE = 3,

    /** @brief �ߵ�ƽ���� */
    TRIGGER_HIGH_LEVEL = 4,

} dvpTriggerInputType;


/** @brief Strobe����ź�����*/
typedef enum dvpStrobeOutputType
{
    /** @brief Strobe����ر� */
    STROBE_OUT_OFF = 0,

    /** @brief ����͵�ƽ */
    STROBE_OUT_LOW = 1,

    /** @brief ����ߵ�ƽ */
    STROBE_OUT_HIGH = 2,

} dvpStrobeOutputType;


/** @brief Strobe�ź�������ʽ*/
typedef enum dvpStrobeDriver
{
    /** @brief ����֡���ڶ���Ч */
    FRAME_DURATION = 0,

    /** @brief �ɶ�ʱ������ */
    TIMER_LOGIC = 1,

    /** @brief ����SENSOR��Strobe�ź� */
    SENSOR_STROBE = 2,

} dvpStrobeDriver;


/** @brief ���ģʽ*/
typedef enum dvpOutputIoFunction
{
    /** @brief ��ͨ��� */
    OUTPUT_FUNCTION_NORMAL = 0x0000,

    /** @brief �������� */
    OUTPUT_FUNCTION_STROBE = 0x0001,

} dvpOutputIoFunction;


/** @brief ����ģʽ*/
typedef enum dvpInputIoFunction
{
    /** @brief ��ͨ���� */
    INPUT_FUNCTION_NORMAL = 0x8001,

    /** @brief �������� */
    INPUT_FUNCTION_TRIGGER = 0x8002,

} dvpInputIoFunction;


/** @brief ���IO*/
typedef enum dvpOutputIo
{
    /** @brief ���1 */
    OUTPUT_IO_1 = 0x0001,

    /** @brief ���2 */
    OUTPUT_IO_2 = 0x0002,

    /** @brief ���3 */
    OUTPUT_IO_3 = 0x0003,

    /** @brief ���4 */
    OUTPUT_IO_4 = 0x0004,

    /** @brief ���5 */
    OUTPUT_IO_5 = 0x0005,

    /** @brief ���6 */
    OUTPUT_IO_6 = 0x0006,

    /** @brief ���7 */
    OUTPUT_IO_7 = 0x0007,

    /** @brief ���8 */
    OUTPUT_IO_8 = 0x0008,

} dvpOutputIo;


/** @brief ����IO*/
typedef enum dvpInputIo
{
    /** @brief ����1 */
    INPUT_IO_1 = 0x8001,

    /** @brief ����2 */
    INPUT_IO_2 = 0x8002,

    /** @brief ����3 */
    INPUT_IO_3 = 0x8003,

    /** @brief ����4 */
    INPUT_IO_4 = 0x8004,

    /** @brief ����5 */
    INPUT_IO_5 = 0x8005,

    /** @brief ����6 */
    INPUT_IO_6 = 0x8006,

    /** @brief ����7 */
    INPUT_IO_7 = 0x8007,

    /** @brief ����8 */
    INPUT_IO_8 = 0x8008,

} dvpInputIo;


/** @brief �豸��ģʽ
*@note ֧��"��"����*/
typedef enum dvpOpenMode
{
    /** @brief ���ߴ� */
    OPEN_OFFLINE = 0,

    /** @brief ��ʵ���豸 */
    OPEN_NORMAL = 1,

    /** @brief �Ե��Է�ʽ���豸������ǧ������������Ա��ⵥ�����Ի�ϵ��������������ʱ */
    OPEN_DEBUG = 1<<3,

} dvpOpenMode;


/** @brief ��Ƶ��״̬*/
typedef enum dvpStreamState
{
    /** @brief ��ֹͣ@see dvpStop */
    STATE_STOPED = 0,

    /** @brief �Ѿ���/��ͣ@see dvpPause */
    STATE_PAUSED = 1,

    /** @brief ������@see dvpStart */
    STATE_STARTED = 2,

} dvpStreamState;


/** @brief ���б�׼�ӿڵ�״̬��*/
typedef enum dvpStatus
{
    /** @brief �������Ե��ˣ�����Ҫ�κζ��� */
    DVP_STATUS_IGNORED = 7,

    /** @brief ��Ҫ�������ݺͲ��� */
    DVP_STATUS_NEED_OTHER = 6,

    /** @brief ���������һ�׶Σ�ֻ����˲��ֶ��� */
    DVP_STATUS_NEXT_STAGE = 5,

    /** @brief ��æ���˴β������ܽ��� */
    DVP_STATUS_BUSY = 4,

    /** @brief ��Ҫ�ȴ��������ٴγ��� */
    DVP_STATUS_WAIT = 3,

    /** @brief ���ڽ��У��Ѿ��������� */
    DVP_STATUS_IN_PROCESS = 2,

    /** @brief �����ɹ� */
    DVP_STATUS_OK = 1,

    /** @brief ����ʧ�� */
    DVP_STATUS_FAILED = 0,

    /** @brief δ֪���� */
    DVP_STATUS_UNKNOW = -1,

    /** @brief ��֧�ָù��� */
    DVP_STATUS_NOT_SUPPORTED = -2,

    /** @brief ��ʼ��δ��� */
    DVP_STATUS_NOT_INITIALIZED = -3,

    /** @brief ������Ч */
    DVP_STATUS_PARAMETER_INVALID = -4,

    /** @brief ����Խ�� */
    DVP_STATUS_PARAMETER_OUT_OF_BOUND = -5,

    /** @brief ����δ�� */
    DVP_STATUS_UNENABLE = -6,

    /** @brief δ���ӵ��豸 */
    DVP_STATUS_UNCONNECTED = -7,

    /** @brief ������Ч */
    DVP_STATUS_NOT_VALID = -8,

    /** @brief �豸û�� */
    DVP_STATUS_UNPLAY = -9,

    /** @brief δ���� */
    DVP_STATUS_NOT_STARTED = -10,

    /** @brief δֹͣ */
    DVP_STATUS_NOT_STOPPED = -11,

    /** @brief δ׼���� */
    DVP_STATUS_NOT_READY = -12,

    /** @brief ��Ч������վ����Ұ�������ͨ�������δ������ */
    DVP_STATUS_INVALID_HANDLE = -13,

    /** @brief ��������� */
    DVP_STATUS_DESCR_FAULT = -20,

    /** @brief ��������� */
    DVP_STATUS_NAME_FAULT = -21,

    /** @brief ����ĸ�ֵ */
    DVP_STATUS_VALUE_FAULT = -22,

    /** @brief ������ */
    DVP_STATUS_LIMITED = -28,

    /** @brief ������Ч */
    DVP_STATUS_FUNCTION_INVALID = -29,

    /** @brief ���Զ������У��ֶ���ʽ��Ч */
    DVP_STATUS_IN_AUTO = -30,

    /** @brief �������ܾ� */
    DVP_STATUS_DENIED = -31,

    /** @brief ƫ�ƻ��ַδ���� */
    DVP_STATUS_BAD_ALIGNMENT = -40,

    /** @brief ��ַ��Ч */
    DVP_STATUS_ADDRESS_INVALID = -41,

    /** @brief ���ݿ��С��Ч */
    DVP_STATUS_SIZE_INVALID = -42,

    /** @brief ���������� */
    DVP_STATUS_OVER_LOAD = -43,

    /** @brief ���������� */
    DVP_STATUS_UNDER_LOAD = -44,

    /** @brief ��顢У��ʧ�� */
    DVP_STATUS_CHECKED_FAILED = -50,

    /** @brief ������ */
    DVP_STATUS_UNUSABLE = -51,

    /** @brief ҵ��ID��Ч��ƥ�� */
    DVP_STATUS_BID_INVALID = -52,

    /** @brief ��ʱ���� */
    DVP_STATUS_TIME_OUT = -1000,

    /** @brief Ӳ��IO���� */
    DVP_STATUS_IO_ERROR = -1001,

    /** @brief ͨѶ���� */
    DVP_STATUS_COMM_ERROR = -1002,

    /** @brief ���ߴ��� */
    DVP_STATUS_BUS_ERROR = -1003,

    /** @brief ��ʽ���� */
    DVP_STATUS_FORMAT_INVALID = -1004,

    /** @brief ������Ч */
    DVP_STATUS_CONTENT_INVALID = -1005,

    /** @brief I2C���ߴ��� */
    DVP_STATUS_I2C_FAULT = -1010,

    /** @brief I2C�ȴ�Ӧ��ʱ */
    DVP_STATUS_I2C_ACK_TIMEOUT = -1011,

    /** @brief I2C�ȴ����߶�����ʱ������SCL���ⲿ������Ϊ�͵�ƽ */
    DVP_STATUS_I2C_BUS_TIMEOUT = -1012,

    /** @brief SPI���ߴ��� */
    DVP_STATUS_SPI_FAULT = -1020,

    /** @brief UART���ߴ��� */
    DVP_STATUS_UART_FAULT = -1030,

    /** @brief GPIO���ߴ��� */
    DVP_STATUS_GPIO_FAULT = -1040,

    /** @brief USB���ߴ��� */
    DVP_STATUS_USB_FAULT = -1050,

    /** @brief PCI���ߴ��� */
    DVP_STATUS_PCI_FAULT = -1060,

    /** @brief �������� */
    DVP_STATUS_PHY_FAULT = -1070,

    /** @brief ��·����� */
    DVP_STATUS_LINK_FAULT = -1080,

    /** @brief �������� */
    DVP_STATUS_TRANS_FAULT = -1090,

    /** @brief û�з����豸 */
    DVP_STATUS_NO_DEVICE_FOUND = -1100,

    /** @brief δ�ҵ��߼��豸 */
    DVP_STATUS_NO_LOGIC_DEVICE_FOUND = -1101,

    /** @brief �豸�Ѿ��� */
    DVP_STATUS_DEVICE_IS_OPENED = -1102,

    /** @brief �豸�Ѿ��ر� */
    DVP_STATUS_DEVICE_IS_CLOSED = -1103,

    /** @brief �豸�Ѿ��Ͽ����� */
    DVP_STATUS_DEVICE_IS_DISCONNECTED = -1104,

    /** @brief �豸�Ѿ������������� */
    DVP_STATUS_DEVICE_IS_OPENED_BY_ANOTHER = -1105,

    /** @brief �豸�Ѿ������� */
    DVP_STATUS_DEVICE_IS_STARTED = -1106,

    /** @brief �豸�Ѿ���ֹͣ�豸�Ѿ������������� */
    DVP_STATUS_DEVICE_IS_STOPPED = -1107,

    /** @brief û���㹻ϵͳ�ڴ� */
    DVP_STATUS_INSUFFICIENT_MEMORY = -1200,

    /** @brief �洢����д����������޷�������д */
    DVP_STATUS_MEMORY_FAULT = -1201,

    /** @brief д����������д */
    DVP_STATUS_WRITE_PROTECTED = -1202,

    /** @brief �����ļ�ʧ�� */
    DVP_STATUS_FILE_CREATE_FAILED = -1300,

    /** @brief �ļ���ʽ��Ч */
    DVP_STATUS_FILE_INVALID = -1301,

    /** @brief ��ȡ�ļ�ʧ�� */
    DVP_STATUS_FILE_READ_FAILED = -1302,

    /** @brief д���ļ�ʧ�� */
    DVP_STATUS_FILE_WRITE_FAILED = -1303,

    /** @brief ���ļ�ʧ�� */
    DVP_STATUS_FILE_OPEN_FAILED = -1304,

    /** @brief ��ȡ���ݽϼ�ʧ�� */
    DVP_STATUS_FILE_CHECKSUM_FAILED = -1305,

    /** @brief ���ݲɼ�ʧ�ܣ�ָ����ʱ����δ������� */
    DVP_STATUS_GRAB_FAILED = -1600,

    /** @brief ���ݶ�ʧ�������� */
    DVP_STATUS_LOST_DATA = -1601,

    /** @brief δ���յ�֡������ */
    DVP_STATUS_EOF_ERROR = -1602,

    /** @brief ���ݲɼ������Ѿ��� */
    DVP_STATUS_GRAB_IS_OPENED = -1603,

    /** @brief ���ݲɼ������Ѿ��ر� */
    DVP_STATUS_GRAB_IS_CLOSED = -1604,

    /** @brief ���ݲɼ��Ѿ����� */
    DVP_STATUS_GRAB_IS_STARTED = -1605,

    /** @brief ���ݲɼ��Ѿ�ֹͣ */
    DVP_STATUS_GRAB_IS_STOPPED = -1606,

    /** @brief ���ݲɼ��������� */
    DVP_STATUS_GRAB_IS_RESTARTING = -1607,

    /** @brief ���õ�ROI������Ч */
    DVP_STATUS_ROI_PARAM_INVALID = -1610,

    /** @brief ROI���ܲ�֧�� */
    DVP_STATUS_ROI_NOT_SUPPORTED = -1611,

} dvpStatus;


/** @} end of __DVP2_ENUM__ */
/** @brief 64�ֽڳ����ַ��� */
typedef char dvpString64[64];

/** @brief 128�ֽڳ����ַ��� */
typedef char dvpString128[128];

/** @brief 32�ֽڳ��Ĳ������� */
typedef bool dvpBool32[32];

/** @brief 32λ�з������� */
typedef signed int dvpInt32;

/** @brief 32λ�޷������� */
typedef unsigned int dvpUint32;

/** @brief 64λ�з������� */
typedef signed __int64 dvpInt64;

/** @brief 64λ�޷������� */
typedef unsigned __int64 dvpUint64;

/** @brief 4��3�м򵥾��� */
typedef float dvpMatrix[4][3];

/** @brief ������
*@see dvpOpen
*@see dvpOpenByName */
typedef dvpUint32 dvpHandle;

/** @brief ��Ƶ���������
*@see dvpStartVideoRecord */
typedef dvpUint32 dvpRecordHandle;

/** @brief ��ɫ���� */
typedef struct dvpColorMatrix
{
    /** @brief ���� */
    dvpMatrix matrix;

    /** @brief �����ֽ� */
    dvpInt32 reserved[32];
} dvpColorMatrix;


/** @brief �����Ϣ 
*@see dvpGetCameraInfo
*@see dvpEnum */
typedef struct dvpCameraInfo
{
    /** @brief ��Ƴ��� */
    dvpString64 Vendor;

    /** @brief �������� */
    dvpString64 Manufacturer;

    /** @brief �ͺ� */
    dvpString64 Model;

    /** @brief ϵ�� */
    dvpString64 Family;

    /** @brief ������ */
    dvpString64 LinkName;

    /** @brief ���������� */
    dvpString64 SensorInfo;

    /** @brief Ӳ���汾 */
    dvpString64 HardwareVersion;

    /** @brief �̼��汾 */
    dvpString64 FirmwareVersion;

    /** @brief �ں������汾 */
    dvpString64 KernelVersion;

    /** @brief �豸�����汾 */
    dvpString64 DscamVersion;

    /** @brief �Ѻ��豸���� */
    dvpString64 FriendlyName;

    /** @brief �ӿ����� */
    dvpString64 PortInfo;

    /** @brief ���к� */
    dvpString64 SerialNumber;

    /** @brief ������� */
    dvpString128 CameraInfo;

    /** @brief �û���ʶ */
    dvpString128 UserID;

    /** @brief �����ֽ� */
    char reserved[128];
} dvpCameraInfo;


/** @brief �������� */
typedef struct dvpRegionDescr
{
    /** @brief ��С��� */
    dvpInt32 iMinW;

    /** @brief ��С�߶� */
    dvpInt32 iMinH;

    /** @brief ����� */
    dvpInt32 iMaxW;

    /** @brief ���߶� */
    dvpInt32 iMaxH;

    /** @brief ��Ȳ��� */
    dvpInt32 iStepW;

    /** @brief �߶Ȳ��� */
    dvpInt32 iStepH;

    /** @brief �����ֽ� */
    dvpInt32 reserved[32];
} dvpRegionDescr;


/** @brief ����Ȥ������
*@see dvpGetRoi
*@see dvpGetAwbRoi
*@see dvpGetAeRoi */
typedef struct dvpRegion
{
    /** @brief ����ƫ�ƣ������� */
    dvpInt32 X;

    /** @brief ����ƫ�ƣ��ϸ����� */
    dvpInt32 Y;

    /** @brief ��� */
    dvpInt32 W;

    /** @brief �߶� */
    dvpInt32 H;

    /** @brief �����ֽ� */
    dvpInt32 reserved[32];
} dvpRegion;


/** @brief ֡��Ϣ
*@see dvpGetFrame */
typedef struct dvpFrame
{
    /** @brief ��ʽ */
    enum dvpImageFormat format;

    /** @brief λ�� */
    enum dvpBits bits;

    /** @brief �ֽ��� */
    dvpUint32 uBytes;

    /** @brief ��� */
    dvpInt32 iWidth;

    /** @brief �߶� */
    dvpInt32 iHeight;

    /** @brief ֡��� */
    dvpUint64 uFrameID;

    /** @brief ʱ��� */
    dvpUint64 uTimestamp;

    /** @brief �ع�ʱ�䣨΢�룩 */
    double fExposure;

    /** @brief ģ������ */
    float fAGain;

    /** @brief �����ֽ� */
    dvpInt32 reserved[32];
} dvpFrame;


/** @brief ������������ */
typedef struct dvpIntDescr
{
    /** @brief ���� */
    dvpInt32 iStep;

    /** @brief ��Сֵ */
    dvpInt32 iMin;

    /** @brief ���ֵ */
    dvpInt32 iMax;

    /** @brief Ĭ��ֵ */
    dvpInt32 iDefault;

    /** @brief �����ֽ� */
    dvpInt32 reserved[32];
} dvpIntDescr;


/** @brief �������������� */
typedef struct dvpFloatDescr
{
    /** @brief ���� */
    float fStep;

    /** @brief ��Сֵ */
    float fMin;

    /** @brief ���ֵ */
    float fMax;

    /** @brief Ĭ��ֵ */
    float fDefault;

    /** @brief �����ֽ� */
    dvpInt32 reserved[32];
} dvpFloatDescr;


/** @brief ˫�������������� */
typedef struct dvpDoubleDescr
{
    /** @brief ���� */
    double fStep;

    /** @brief ��Сֵ */
    double fMin;

    /** @brief ���ֵ */
    double fMax;

    /** @brief Ĭ��ֵ */
    double fDefault;

    /** @brief �����ֽ� */
    dvpInt32 reserved[32];
} dvpDoubleDescr;


/** @brief 64λ�޷��������������� */
typedef struct dvpUint64Descr
{
    /** @brief ���� */
    dvpUint64 uStep;

    /** @brief ��Сֵ */
    dvpUint64 uMin;

    /** @brief ���ֵ */
    dvpUint64 uMax;

    /** @brief Ĭ��ֵ */
    dvpUint64 uDefault;

    /** @brief �����ֽ� */
    dvpInt32 reserved[32];
} dvpUint64Descr;


/** @brief ѡ�������� */
typedef struct dvpSelectionDescr
{
    /** @brief Ĭ������ */
    dvpUint32 uDefault;

    /** @brief �������� */
    dvpUint32 uCount;

    /** @brief �Ƿ�Ӧֹͣ��Ƶ�� */
    bool bNeedStop;

    /** @brief �����ֽ� */
    dvpInt32 reserved[32];
} dvpSelectionDescr;


/** @brief ѡ���� */
typedef struct dvpSelection
{
    /** @brief �ַ������� */
    dvpString64 string;

    /** @brief ���� */
    dvpInt32 iIndex;

    /** @brief �����ֽ� */
    dvpInt32 reserved[32];
} dvpSelection;


/** @brief �ֱ���ģʽ
*@see dvpGetTriggerModeSelDetail */
typedef struct dvpResolutionMode
{
    /** @brief �ֱ���ģʽѡ���� */
    struct dvpSelection selection;

    /** @brief ���� */
    struct dvpRegionDescr region;

    /** @brief �����ֽ� */
    dvpInt32 reserved[32];
} dvpResolutionMode;


/** @brief ����Roi
*@see dvpGetQuickRoiSelDetail */
typedef struct dvpQuickRoi
{
    /** @brief ѡ���� */
    struct dvpSelection selection;

    /** @brief ����Ȥ������ */
    struct dvpRegion roi;

    /** @brief �ֱ���ģʽ */
    struct dvpResolutionMode mode;

    /** @brief �����ֽ� */
    dvpInt32 reserved[32];
} dvpQuickRoi;


/** @brief ֡����
@see dvpGetFrameCount */
typedef struct dvpFrameCount
{
    /** @brief ��֡�� */
    dvpUint32 uFrameCount;

    /** @brief ��ʧ֡������������ȡ�� */
    dvpUint32 uFrameDrop;

    /** @brief �����ģ��ɼ��󱻶����� */
    dvpUint32 uFrameIgnore;

    /** @brief ����֡���� */
    dvpUint32 uFrameError;

    /** @brief ���ɼ�������ȷ֡ */
    dvpUint32 uFrameOK;

    /** @brief ���ύ / �������Ч֡ */
    dvpUint32 uFrameOut;

    /** @brief �ش�֡ */
    dvpUint32 uFrameResend;

    /** @brief ͼ����֡���� */
    dvpUint32 uFrameProc;

    /** @brief �ɼ�֡�� */
    float fFrameRate;

    /** @brief ͼ����֡�� */
    float fProcRate;

    /** @brief �����ֽ� */
    dvpInt32 reserved[32];
} dvpFrameCount;


/** @brief �û�IO��Ϣ
@see dvpGetUserIoInfo */
typedef struct dvpUserIoInfo
{
    /** @brief ���õ�����IO */
    dvpBool32 inputValid;

    /** @brief ���õ����IO */
    dvpBool32 outputValid;

    /** @brief �����ֽ� */
    dvpInt32 reserved[32];
} dvpUserIoInfo;


/** @brief Sensor(ͼ�񴫸���)��Ϣ
@see dvpGetSensorInfo */
typedef struct dvpSensorInfo
{
    /** @brief �ַ������� */
    dvpString64 descr;

    /** @brief ���������� */
    enum dvpSensorType sensor;

    /** @brief ԭʼ�������� */
    enum dvpSensorPixel pixel;

    /** @brief ���� */
    struct dvpRegionDescr region;

    /** @brief �����ֽ� */
    dvpInt32 reserved[32];
} dvpSensorInfo;



/** @defgroup __DVP2_API__ API
*@{
*/
/**
*@brief ��ȡ�����Ϣ
*@param[in] handle ������
*@param[out] pCameraInfo �����Ϣ
*@return ״̬��
*@ingroup __DVP_INFORMATION__
*/
dvp2api dvpStatus dvpGetCameraInfo(dvpHandle handle, dvpCameraInfo *pCameraInfo);


/**
*@brief ��ȡ��������Ϣ
*@param[in] handle ������
*@param[out] pSensorInfo ��������Ϣ
*@return ״̬��
*@ingroup __DVP_INFORMATION__
*/
dvp2api dvpStatus dvpGetSensorInfo(dvpHandle handle, dvpSensorInfo *pSensorInfo);


/**
*@brief ��ȡ֡����
*@param[in] handle ������
*@param[out] pFrameCount ֡����
*@return ״̬��
*@ingroup __DVP_INFORMATION__
*/
dvp2api dvpStatus dvpGetFrameCount(dvpHandle handle, dvpFrameCount *pFrameCount);


/**
*@brief ��ȡ�û�IO��Ч��־
*@param[in] handle ������
*@param[out] pUserIoInfo �û�IO��Ч��־
*@return ״̬��
*@ingroup __DVP_INFORMATION__
*/
dvp2api dvpStatus dvpGetUserIoInfo(dvpHandle handle, dvpUserIoInfo *pUserIoInfo);


/**
*@brief ������������ź�
*@param[in] handle ������
*@return ״̬��
*@ingroup __DVP_TRIGGER__
*/
dvp2api dvpStatus dvpTriggerFire(dvpHandle handle);


/**
*@brief �����ʵ���Ϣ
*@param[in] handle ������
*@return ״̬��
*@ingroup __DVP_ADVANCED__
*/
dvp2api dvpStatus dvpCreateDefectFixInfo(dvpHandle handle);


/**
*@brief ����ƽ����Ϣ
*@param[in] handle ������
*@return ״̬��
*@ingroup __DVP_ADVANCED__
*/
dvp2api dvpStatus dvpCreateFlatFieldInfo(dvpHandle handle);


/**
*@brief ������Ƶ��
*@param[in] handle ������
*@return ״̬��
*@ingroup __DVP_ADVANCED__
*/
dvp2api dvpStatus dvpRestart(dvpHandle handle);


/**
*@brief ��ȡ��ɫ���������������Ϣ
*@param[in] handle ������
*@param[out] pRGainDescr ��ɫ���������������Ϣ
*@return ״̬��
*@ingroup __DVP_COLOR__
*@see dvpSetRgbGainState
*@see dvpGetRgbGainState
*@see dvpSetRgbGain
*@see dvpGetRgbGain
*/
dvp2api dvpStatus dvpGetRGainDescr(dvpHandle handle, dvpFloatDescr *pRGainDescr);


/**
*@brief ��ȡ��ɫ���������������Ϣ
*@param[in] handle ������
*@param[out] pGGainDescr ��ɫ���������������Ϣ
*@return ״̬��
*@ingroup __DVP_COLOR__
*@see dvpSetRgbGainState
*@see dvpGetRgbGainState
*@see dvpSetRgbGain
*@see dvpGetRgbGain
*/
dvp2api dvpStatus dvpGetGGainDescr(dvpHandle handle, dvpFloatDescr *pGGainDescr);

/**
*@brief ��ȡ��ɫ���������������Ϣ
*@param[in] handle ������
*@param[out] pBGainDescr ��ɫ���������������Ϣ
*@return ״̬��
*@ingroup __DVP_COLOR__
*@see dvpSetRgbGainState
*@see dvpGetRgbGainState
*@see dvpSetRgbGain
*@see dvpGetRgbGain
*/
dvp2api dvpStatus dvpGetBGainDescr(dvpHandle handle, dvpFloatDescr *pBGainDescr);

/**
*@brief ��ȡ٤���ֵ
*@param[in] handle ������
*@param[out] pGamma ٤���ֵ
*@return ״̬��
*@ingroup __DVP_ENHANCE__
*@see dvpSetGammaState
*@see dvpGetGammaState
*@see dvpGetGammaDescr
*@see dvpSetGamma
*/
dvp2api dvpStatus dvpGetGamma(dvpHandle handle, dvpInt32 *pGamma);


/**
*@brief ����٤���ֵ
*@param[in] handle ������
*@param[in] Gamma ٤���ֵ
*@return ״̬��
*@ingroup __DVP_ENHANCE__
*@see dvpSetGammaState
*@see dvpGetGammaState
*@see dvpGetGammaDescr
*@see dvpGetGamma
*/
dvp2api dvpStatus dvpSetGamma(dvpHandle handle, dvpInt32 Gamma);


/**
*@brief ��ȡ٤���������Ϣ
*@param[in] handle ������
*@param[out] pGammaDescr ٤���������Ϣ
*@return ״̬��
*@ingroup __DVP_ENHANCE__
*@see dvpSetGammaState
*@see dvpGetGammaState
*@see dvpSetGamma
*@see dvpGetGamma
*/
dvp2api dvpStatus dvpGetGammaDescr(dvpHandle handle, dvpIntDescr *pGammaDescr);


/**
*@brief ��ȡ٤�깦�ܵ�ʹ��״̬
*@param[in] handle ������
*@param[out] pGammaState ٤�깦�ܵ�ʹ��״̬
*@return ״̬��
*@ingroup __DVP_ENHANCE__
*@see dvpSetGamma
*@see dvpGetGamma
*@see dvpGetGammaDescr
*@see dvpSetGammaState
*/
dvp2api dvpStatus dvpGetGammaState(dvpHandle handle, bool *pGammaState);


/**
*@brief ����٤�깦�ܵ�ʹ��״̬
*@param[in] handle ������
*@param[in] GammaState ٤�깦�ܵ�ʹ��״̬
*@return ״̬��
*@ingroup __DVP_ENHANCE__
*@see dvpSetGamma
*@see dvpGetGamma
*@see dvpGetGammaDescr
*@see dvpGetGammaState
*/
dvp2api dvpStatus dvpSetGammaState(dvpHandle handle, bool GammaState);


/**
*@brief ��ȡ�Աȶȵ�ֵ
*@param[in] handle ������
*@param[out] pContrast �Աȶȵ�ֵ
*@return ״̬��
*@ingroup __DVP_ENHANCE__
*@see dvpSetContrastState
*@see dvpGetContrastState
*@see dvpGetContrastDescr
*@see dvpSetContrast
*/
dvp2api dvpStatus dvpGetContrast(dvpHandle handle, dvpInt32 *pContrast);


/**
*@brief ���öԱȶȵ�ֵ
*@param[in] handle ������
*@param[in] Contrast �Աȶȵ�ֵ
*@return ״̬��
*@ingroup __DVP_ENHANCE__
*@see dvpSetContrastState
*@see dvpGetContrastState
*@see dvpGetContrastDescr
*@see dvpGetContrast
*/
dvp2api dvpStatus dvpSetContrast(dvpHandle handle, dvpInt32 Contrast);


/**
*@brief ��ȡ�Աȶȵ�������Ϣ
*@param[in] handle ������
*@param[out] pContrastDescr �Աȶȵ�������Ϣ
*@return ״̬��
*@ingroup __DVP_ENHANCE__
*@see dvpSetContrastState
*@see dvpGetContrastState
*@see dvpSetContrast
*@see dvpGetContrast
*/
dvp2api dvpStatus dvpGetContrastDescr(dvpHandle handle, dvpIntDescr *pContrastDescr);


/**
*@brief ��ȡ�Աȶȹ��ܵ�ʹ��״̬
*@param[in] handle ������
*@param[out] pContrastState �Աȶȹ��ܵ�ʹ��״̬
*@return ״̬��
*@ingroup __DVP_ENHANCE__
*@see dvpSetContrast
*@see dvpGetContrast
*@see dvpGetContrastDescr
*@see dvpSetContrastState
*/
dvp2api dvpStatus dvpGetContrastState(dvpHandle handle, bool *pContrastState);


/**
*@brief ���öԱȶȹ��ܵ�ʹ��״̬
*@param[in] handle ������
*@param[in] ContrastState �Աȶȹ��ܵ�ʹ��״̬
*@return ״̬��
*@ingroup __DVP_ENHANCE__
*@see dvpSetContrast
*@see dvpGetContrast
*@see dvpGetContrastDescr
*@see dvpGetContrastState
*/
dvp2api dvpStatus dvpSetContrastState(dvpHandle handle, bool ContrastState);


/**
*@brief ��ȡͼ��Roi(����Ȥ������)
*@param[in] handle ������
*@param[out] pRoi ͼ��Roi(����Ȥ������)
*@return ״̬��
*@ingroup __DVP_SIZE__
*@see dvpSetRoiState
*@see dvpGetRoiState
*@see dvpGetRoiDescr
*@see dvpSetRoi
*/
dvp2api dvpStatus dvpGetRoi(dvpHandle handle, dvpRegion *pRoi);


/**
*@brief ����ͼ��Roi(����Ȥ������)
*@param[in] handle ������
*@param[in] Roi ͼ��Roi(����Ȥ������)
*@return ״̬��
*@ingroup __DVP_SIZE__
*@see dvpSetRoiState
*@see dvpGetRoiState
*@see dvpGetRoiDescr
*@see dvpGetRoi
*/
dvp2api dvpStatus dvpSetRoi(dvpHandle handle, dvpRegion Roi);


/**
*@brief ��ȡͼ��Roi(����Ȥ������)��������Ϣ
*@param[in] handle ������
*@param[out] pRoiDescr ͼ��Roi(����Ȥ������)��������Ϣ
*@return ״̬��
*@ingroup __DVP_SIZE__
*@see dvpSetRoiState
*@see dvpGetRoiState
*@see dvpSetRoi
*@see dvpGetRoi
*/
dvp2api dvpStatus dvpGetRoiDescr(dvpHandle handle, dvpRegionDescr *pRoiDescr);


/**
*@brief ��ȡͼ��Roi(����Ȥ������)���ܵ�ʹ��״̬
*@param[in] handle ������
*@param[out] pRoiState ͼ��Roi(����Ȥ������)���ܵ�ʹ��״̬
*@return ״̬��
*@ingroup __DVP_SIZE__
*@see dvpSetRoi
*@see dvpGetRoi
*@see dvpGetRoiDescr
*@see dvpSetRoiState
*/
dvp2api dvpStatus dvpGetRoiState(dvpHandle handle, bool *pRoiState);


/**
*@brief ����ͼ��Roi(����Ȥ������)���ܵ�ʹ��״̬
*@param[in] handle ������
*@param[in] RoiState ͼ��Roi(����Ȥ������)���ܵ�ʹ��״̬
*@return ״̬��
*@ingroup __DVP_SIZE__
*@see dvpSetRoi
*@see dvpGetRoi
*@see dvpGetRoiDescr
*@see dvpGetRoiState
*/
dvp2api dvpStatus dvpSetRoiState(dvpHandle handle, bool RoiState);


/**
*@brief ��ȡɫ�µ�ֵ����λΪK��
*@param[in] handle ������
*@param[out] pColorTemperature ɫ�µ�ֵ����λΪK��
*@return ״̬��
*@ingroup __DVP_COLOR__
*@see dvpSetColorTemperatureState
*@see dvpGetColorTemperatureState
*@see dvpGetColorTemperatureDescr
*@see dvpSetColorTemperature
*/
dvp2api dvpStatus dvpGetColorTemperature(dvpHandle handle, dvpInt32 *pColorTemperature);


/**
*@brief ����ɫ�µ�ֵ����λΪK��
*@param[in] handle ������
*@param[in] ColorTemperature ɫ�µ�ֵ����λΪK��
*@return ״̬��
*@ingroup __DVP_COLOR__
*@see dvpSetColorTemperatureState
*@see dvpGetColorTemperatureState
*@see dvpGetColorTemperatureDescr
*@see dvpGetColorTemperature
*/
dvp2api dvpStatus dvpSetColorTemperature(dvpHandle handle, dvpInt32 ColorTemperature);


/**
*@brief ��ȡɫ�µ�������Ϣ
*@param[in] handle ������
*@param[out] pColorTemperatureDescr ɫ�µ�������Ϣ
*@return ״̬��
*@ingroup __DVP_COLOR__
*@see dvpSetColorTemperatureState
*@see dvpGetColorTemperatureState
*@see dvpSetColorTemperature
*@see dvpGetColorTemperature
*/
dvp2api dvpStatus dvpGetColorTemperatureDescr(dvpHandle handle, dvpIntDescr *pColorTemperatureDescr);


/**
*@brief ��ȡɫ�¹��ܵ�ʹ��״̬
*@param[in] handle ������
*@param[out] pColorTemperatureState ɫ�¹��ܵ�ʹ��״̬
*@return ״̬��
*@ingroup __DVP_COLOR__
*@see dvpSetColorTemperature
*@see dvpGetColorTemperature
*@see dvpGetColorTemperatureDescr
*@see dvpSetColorTemperatureState
*/
dvp2api dvpStatus dvpGetColorTemperatureState(dvpHandle handle, bool *pColorTemperatureState);


/**
*@brief ����ɫ�¹��ܵ�ʹ��״̬
*@param[in] handle ������
*@param[in] ColorTemperatureState ɫ�¹��ܵ�ʹ��״̬
*@return ״̬��
*@ingroup __DVP_COLOR__
*@see dvpSetColorTemperature
*@see dvpGetColorTemperature
*@see dvpGetColorTemperatureDescr
*@see dvpGetColorTemperatureState
*/
dvp2api dvpStatus dvpSetColorTemperatureState(dvpHandle handle, bool ColorTemperatureState);


/**
*@brief ��ȡ��ȵ�ֵ
*@param[in] handle ������
*@param[out] pSharpness ��ȵ�ֵ
*@return ״̬��
*@ingroup __DVP_ENHANCE__
*@see dvpSetSharpnessState
*@see dvpGetSharpnessState
*@see dvpGetSharpnessDescr
*@see dvpSetSharpness
*/
dvp2api dvpStatus dvpGetSharpness(dvpHandle handle, dvpInt32 *pSharpness);


/**
*@brief ������ȵ�ֵ
*@param[in] handle ������
*@param[in] Sharpness ��ȵ�ֵ
*@return ״̬��
*@ingroup __DVP_ENHANCE__
*@see dvpSetSharpnessState
*@see dvpGetSharpnessState
*@see dvpGetSharpnessDescr
*@see dvpGetSharpness
*/
dvp2api dvpStatus dvpSetSharpness(dvpHandle handle, dvpInt32 Sharpness);


/**
*@brief ��ȡ��ȵ�������Ϣ
*@param[in] handle ������
*@param[out] pSharpnessDescr ��ȵ�������Ϣ
*@return ״̬��
*@ingroup __DVP_ENHANCE__
*@see dvpSetSharpnessState
*@see dvpGetSharpnessState
*@see dvpSetSharpness
*@see dvpGetSharpness
*/
dvp2api dvpStatus dvpGetSharpnessDescr(dvpHandle handle, dvpIntDescr *pSharpnessDescr);


/**
*@brief ��ȡ��ȹ��ܵ�ʹ��״̬
*@param[in] handle ������
*@param[out] pSharpnessState ��ȹ��ܵ�ʹ��״̬
*@return ״̬��
*@ingroup __DVP_ENHANCE__
*@see dvpSetSharpness
*@see dvpGetSharpness
*@see dvpGetSharpnessDescr
*@see dvpSetSharpnessState
*/
dvp2api dvpStatus dvpGetSharpnessState(dvpHandle handle, bool *pSharpnessState);


/**
*@brief ������ȹ��ܵ�ʹ��״̬
*@param[in] handle ������
*@param[in] SharpnessState ��ȹ��ܵ�ʹ��״̬
*@return ״̬��
*@ingroup __DVP_ENHANCE__
*@see dvpSetSharpness
*@see dvpGetSharpness
*@see dvpGetSharpnessDescr
*@see dvpGetSharpnessState
*/
dvp2api dvpStatus dvpSetSharpnessState(dvpHandle handle, bool SharpnessState);


/**
*@brief ��ȡ���Ͷȵ�ֵ
*@param[in] handle ������
*@param[out] pSaturation ���Ͷȵ�ֵ
*@return ״̬��
*@ingroup __DVP_COLOR__
*@see dvpSetSaturationState
*@see dvpGetSaturationState
*@see dvpGetSaturationDescr
*@see dvpSetSaturation
*/
dvp2api dvpStatus dvpGetSaturation(dvpHandle handle, dvpInt32 *pSaturation);


/**
*@brief ���ñ��Ͷȵ�ֵ
*@param[in] handle ������
*@param[in] Saturation ���Ͷȵ�ֵ
*@return ״̬��
*@ingroup __DVP_COLOR__
*@see dvpSetSaturationState
*@see dvpGetSaturationState
*@see dvpGetSaturationDescr
*@see dvpGetSaturation
*/
dvp2api dvpStatus dvpSetSaturation(dvpHandle handle, dvpInt32 Saturation);


/**
*@brief ��ȡ���Ͷȵ�������Ϣ
*@param[in] handle ������
*@param[out] pSaturationDescr ���Ͷȵ�������Ϣ
*@return ״̬��
*@ingroup __DVP_COLOR__
*@see dvpSetSaturationState
*@see dvpGetSaturationState
*@see dvpSetSaturation
*@see dvpGetSaturation
*/
dvp2api dvpStatus dvpGetSaturationDescr(dvpHandle handle, dvpIntDescr *pSaturationDescr);


/**
*@brief ��ȡ���Ͷȹ��ܵ�ʹ��״̬
*@param[in] handle ������
*@param[out] pSaturationState ���Ͷȹ��ܵ�ʹ��״̬
*@return ״̬��
*@ingroup __DVP_COLOR__
*@see dvpSetSaturation
*@see dvpGetSaturation
*@see dvpGetSaturationDescr
*@see dvpSetSaturationState
*/
dvp2api dvpStatus dvpGetSaturationState(dvpHandle handle, bool *pSaturationState);


/**
*@brief ���ñ��Ͷȹ��ܵ�ʹ��״̬
*@param[in] handle ������
*@param[in] SaturationState ���Ͷȹ��ܵ�ʹ��״̬
*@return ״̬��
*@ingroup __DVP_COLOR__
*@see dvpSetSaturation
*@see dvpGetSaturation
*@see dvpGetSaturationDescr
*@see dvpGetSaturationState
*/
dvp2api dvpStatus dvpSetSaturationState(dvpHandle handle, bool SaturationState);


/**
*@brief ��ȡ2D�����ֵ
*@param[in] handle ������
*@param[out] pNoiseReduct2d 2D�����ֵ
*@return ״̬��
*@ingroup __DVP_ENHANCE__
*@see dvpSetNoiseReduct2dState
*@see dvpGetNoiseReduct2dState
*@see dvpGetNoiseReduct2dDescr
*@see dvpSetNoiseReduct2d
*/
dvp2api dvpStatus dvpGetNoiseReduct2d(dvpHandle handle, dvpInt32 *pNoiseReduct2d);


/**
*@brief ����2D�����ֵ
*@param[in] handle ������
*@param[in] NoiseReduct2d 2D�����ֵ
*@return ״̬��
*@ingroup __DVP_ENHANCE__
*@see dvpSetNoiseReduct2dState
*@see dvpGetNoiseReduct2dState
*@see dvpGetNoiseReduct2dDescr
*@see dvpGetNoiseReduct2d
*/
dvp2api dvpStatus dvpSetNoiseReduct2d(dvpHandle handle, dvpInt32 NoiseReduct2d);


/**
*@brief ��ȡ2D�����������Ϣ
*@param[in] handle ������
*@param[out] pNoiseReduct2dDescr 2D�����������Ϣ
*@return ״̬��
*@ingroup __DVP_ENHANCE__
*@see dvpSetNoiseReduct2dState
*@see dvpGetNoiseReduct2dState
*@see dvpSetNoiseReduct2d
*@see dvpGetNoiseReduct2d
*/
dvp2api dvpStatus dvpGetNoiseReduct2dDescr(dvpHandle handle, dvpIntDescr *pNoiseReduct2dDescr);


/**
*@brief ��ȡ2D���빦�ܵ�ʹ��״̬
*@param[in] handle ������
*@param[out] pNoiseReduct2dState 2D���빦�ܵ�ʹ��״̬
*@return ״̬��
*@ingroup __DVP_ENHANCE__
*@see dvpSetNoiseReduct2d
*@see dvpGetNoiseReduct2d
*@see dvpGetNoiseReduct2dDescr
*@see dvpSetNoiseReduct2dState
*/
dvp2api dvpStatus dvpGetNoiseReduct2dState(dvpHandle handle, bool *pNoiseReduct2dState);


/**
*@brief ����2D���빦�ܵ�ʹ��״̬
*@param[in] handle ������
*@param[in] NoiseReduct2dState 2D���빦�ܵ�ʹ��״̬
*@return ״̬��
*@ingroup __DVP_ENHANCE__
*@see dvpSetNoiseReduct2d
*@see dvpGetNoiseReduct2d
*@see dvpGetNoiseReduct2dDescr
*@see dvpGetNoiseReduct2dState
*/
dvp2api dvpStatus dvpSetNoiseReduct2dState(dvpHandle handle, bool NoiseReduct2dState);


/**
*@brief ��ȡ3D�����ֵ
*@param[in] handle ������
*@param[out] pNoiseReduct3d 3D�����ֵ
*@return ״̬��
*@ingroup __DVP_ENHANCE__
*@see dvpSetNoiseReduct3dState
*@see dvpGetNoiseReduct3dState
*@see dvpGetNoiseReduct3dDescr
*@see dvpSetNoiseReduct3d
*/
dvp2api dvpStatus dvpGetNoiseReduct3d(dvpHandle handle, dvpInt32 *pNoiseReduct3d);


/**
*@brief ����3D�����ֵ
*@param[in] handle ������
*@param[in] NoiseReduct3d 3D�����ֵ
*@return ״̬��
*@ingroup __DVP_ENHANCE__
*@see dvpSetNoiseReduct3dState
*@see dvpGetNoiseReduct3dState
*@see dvpGetNoiseReduct3dDescr
*@see dvpGetNoiseReduct3d
*/
dvp2api dvpStatus dvpSetNoiseReduct3d(dvpHandle handle, dvpInt32 NoiseReduct3d);


/**
*@brief ��ȡ3D�����������Ϣ
*@param[in] handle ������
*@param[out] pNoiseReduct3dDescr 3D�����������Ϣ
*@return ״̬��
*@ingroup __DVP_ENHANCE__
*@see dvpSetNoiseReduct3dState
*@see dvpGetNoiseReduct3dState
*@see dvpSetNoiseReduct3d
*@see dvpGetNoiseReduct3d
*/
dvp2api dvpStatus dvpGetNoiseReduct3dDescr(dvpHandle handle, dvpIntDescr *pNoiseReduct3dDescr);


/**
*@brief ��ȡ3D���빦�ܵ�ʹ��״̬
*@param[in] handle ������
*@param[out] pNoiseReduct3dState 3D���빦�ܵ�ʹ��״̬
*@return ״̬��
*@ingroup __DVP_ENHANCE__
*@see dvpSetNoiseReduct3d
*@see dvpGetNoiseReduct3d
*@see dvpGetNoiseReduct3dDescr
*@see dvpSetNoiseReduct3dState
*/
dvp2api dvpStatus dvpGetNoiseReduct3dState(dvpHandle handle, bool *pNoiseReduct3dState);


/**
*@brief ����3D���빦�ܵ�ʹ��״̬
*@param[in] handle ������
*@param[in] NoiseReduct3dState 3D���빦�ܵ�ʹ��״̬
*@return ״̬��
*@ingroup __DVP_ENHANCE__
*@see dvpSetNoiseReduct3d
*@see dvpGetNoiseReduct3d
*@see dvpGetNoiseReduct3dDescr
*@see dvpGetNoiseReduct3dState
*/
dvp2api dvpStatus dvpSetNoiseReduct3dState(dvpHandle handle, bool NoiseReduct3dState);


/**
*@brief ��ȡblack level��ֵ
*@param[in] handle ������
*@param[out] pBlackLevel black level��ֵ
*@return ״̬��
*@ingroup __DVP_ENHANCE__
*@see dvpSetBlackLevelState
*@see dvpGetBlackLevelState
*@see dvpGetBlackLevelDescr
*@see dvpSetBlackLevel
*/
dvp2api dvpStatus dvpGetBlackLevel(dvpHandle handle, float *pBlackLevel);


/**
*@brief ����black level��ֵ
*@param[in] handle ������
*@param[in] BlackLevel black level��ֵ
*@return ״̬��
*@ingroup __DVP_ENHANCE__
*@see dvpSetBlackLevelState
*@see dvpGetBlackLevelState
*@see dvpGetBlackLevelDescr
*@see dvpGetBlackLevel
*/
dvp2api dvpStatus dvpSetBlackLevel(dvpHandle handle, float BlackLevel);


/**
*@brief ��ȡblack level��������Ϣ
*@param[in] handle ������
*@param[out] pBlackLevelDescr black level��������Ϣ
*@return ״̬��
*@ingroup __DVP_ENHANCE__
*@see dvpSetBlackLevelState
*@see dvpGetBlackLevelState
*@see dvpSetBlackLevel
*@see dvpGetBlackLevel
*/
dvp2api dvpStatus dvpGetBlackLevelDescr(dvpHandle handle, dvpFloatDescr *pBlackLevelDescr);


/**
*@brief ��ȡblack level���ܵ�ʹ��״̬
*@param[in] handle ������
*@param[out] pBlackLevelState black level���ܵ�ʹ��״̬
*@return ״̬��
*@ingroup __DVP_ENHANCE__
*@see dvpSetBlackLevel
*@see dvpGetBlackLevel
*@see dvpGetBlackLevelDescr
*@see dvpSetBlackLevelState
*/
dvp2api dvpStatus dvpGetBlackLevelState(dvpHandle handle, bool *pBlackLevelState);


/**
*@brief ����black level���ܵ�ʹ��״̬
*@param[in] handle ������
*@param[in] BlackLevelState black level���ܵ�ʹ��״̬
*@return ״̬��
*@ingroup __DVP_ENHANCE__
*@see dvpSetBlackLevel
*@see dvpGetBlackLevel
*@see dvpGetBlackLevelDescr
*@see dvpGetBlackLevelState
*/
dvp2api dvpStatus dvpSetBlackLevelState(dvpHandle handle, bool BlackLevelState);


/**
*@brief ��ȡѭ������������ֵ����λΪ΢�룩
*@param[in] handle ������
*@param[out] pSoftTriggerLoop ѭ������������ֵ����λΪ΢�룩
*@return ״̬��
*@ingroup __DVP_TRIGGER__
*@see dvpSetSoftTriggerLoopState
*@see dvpGetSoftTriggerLoopState
*@see dvpGetSoftTriggerLoopDescr
*@see dvpSetSoftTriggerLoop
*/
dvp2api dvpStatus dvpGetSoftTriggerLoop(dvpHandle handle, double *pSoftTriggerLoop);


/**
*@brief ����ѭ������������ֵ����λΪ΢�룩
*@param[in] handle ������
*@param[in] SoftTriggerLoop ѭ������������ֵ����λΪ΢�룩
*@return ״̬��
*@ingroup __DVP_TRIGGER__
*@see dvpSetSoftTriggerLoopState
*@see dvpGetSoftTriggerLoopState
*@see dvpGetSoftTriggerLoopDescr
*@see dvpGetSoftTriggerLoop
*/
dvp2api dvpStatus dvpSetSoftTriggerLoop(dvpHandle handle, double SoftTriggerLoop);


/**
*@brief ��ȡѭ��������������Ϣ
*@param[in] handle ������
*@param[out] pSoftTriggerLoopDescr ѭ��������������Ϣ
*@return ״̬��
*@ingroup __DVP_TRIGGER__
*@see dvpSetSoftTriggerLoopState
*@see dvpGetSoftTriggerLoopState
*@see dvpSetSoftTriggerLoop
*@see dvpGetSoftTriggerLoop
*/
dvp2api dvpStatus dvpGetSoftTriggerLoopDescr(dvpHandle handle, dvpDoubleDescr *pSoftTriggerLoopDescr);


/**
*@brief ��ȡѭ���������ܵ�ʹ��״̬
*@param[in] handle ������
*@param[out] pSoftTriggerLoopState ѭ���������ܵ�ʹ��״̬
*@return ״̬��
*@ingroup __DVP_TRIGGER__
*@see dvpSetSoftTriggerLoop
*@see dvpGetSoftTriggerLoop
*@see dvpGetSoftTriggerLoopDescr
*@see dvpSetSoftTriggerLoopState
*/
dvp2api dvpStatus dvpGetSoftTriggerLoopState(dvpHandle handle, bool *pSoftTriggerLoopState);


/**
*@brief ����ѭ���������ܵ�ʹ��״̬
*@param[in] handle ������
*@param[in] SoftTriggerLoopState ѭ���������ܵ�ʹ��״̬
*@return ״̬��
*@ingroup __DVP_TRIGGER__
*@see dvpSetSoftTriggerLoop
*@see dvpGetSoftTriggerLoop
*@see dvpGetSoftTriggerLoopDescr
*@see dvpGetSoftTriggerLoopState
*/
dvp2api dvpStatus dvpSetSoftTriggerLoopState(dvpHandle handle, bool SoftTriggerLoopState);


/**
*@brief ��ȡ�����������������ֵ����λΪ΢�룩
*@param[in] handle ������
*@param[out] pStreamPackInterval �����������������ֵ����λΪ΢�룩
*@return ״̬��
*@ingroup __DVP_ADVANCED__
*@see dvpGetStreamPackIntervalDescr
*@see dvpSetStreamPackInterval
*/
dvp2api dvpStatus dvpGetStreamPackInterval(dvpHandle handle, dvpInt32 *pStreamPackInterval);


/**
*@brief ���������������������ֵ����λΪ΢�룩
*@param[in] handle ������
*@param[in] StreamPackInterval �����������������ֵ����λΪ΢�룩
*@return ״̬��
*@ingroup __DVP_ADVANCED__
*@see dvpGetStreamPackIntervalDescr
*@see dvpGetStreamPackInterval
*/
dvp2api dvpStatus dvpSetStreamPackInterval(dvpHandle handle, dvpInt32 StreamPackInterval);


/**
*@brief ��ȡ�����������������������Ϣ
*@param[in] handle ������
*@param[out] pStreamPackIntervalDescr �����������������������Ϣ
*@return ״̬��
*@ingroup __DVP_ADVANCED__
*@see dvpSetStreamPackInterval
*@see dvpGetStreamPackInterval
*/
dvp2api dvpStatus dvpGetStreamPackIntervalDescr(dvpHandle handle, dvpIntDescr *pStreamPackIntervalDescr);


/**
*@brief ��ȡ����������������ֵ����λΪ�ֽڣ�
*@param[in] handle ������
*@param[out] pStreamPackSize ����������������ֵ����λΪ�ֽڣ�
*@return ״̬��
*@ingroup __DVP_ADVANCED__
*@see dvpGetStreamPackSizeDescr
*@see dvpSetStreamPackSize
*/
dvp2api dvpStatus dvpGetStreamPackSize(dvpHandle handle, dvpInt32 *pStreamPackSize);


/**
*@brief ��������������������ֵ����λΪ�ֽڣ�
*@param[in] handle ������
*@param[in] StreamPackSize ����������������ֵ����λΪ�ֽڣ�
*@return ״̬��
*@ingroup __DVP_ADVANCED__
*@see dvpGetStreamPackSizeDescr
*@see dvpGetStreamPackSize
*/
dvp2api dvpStatus dvpSetStreamPackSize(dvpHandle handle, dvpInt32 StreamPackSize);


/**
*@brief ��ȡ����������������������Ϣ
*@param[in] handle ������
*@param[out] pStreamPackSizeDescr ����������������������Ϣ
*@return ״̬��
*@ingroup __DVP_ADVANCED__
*@see dvpSetStreamPackSize
*@see dvpGetStreamPackSize
*/
dvp2api dvpStatus dvpGetStreamPackSizeDescr(dvpHandle handle, dvpIntDescr *pStreamPackSizeDescr);


/**
*@brief ��ȡ�ع�ʱ���ֵ����λΪ΢�룩
*@param[in] handle ������
*@param[out] pExposure �ع�ʱ���ֵ����λΪ΢�룩
*@return ״̬��
*@ingroup __DVP_EXPOSURE__
*@see dvpGetExposureDescr
*@see dvpSetExposure
*/
dvp2api dvpStatus dvpGetExposure(dvpHandle handle, double *pExposure);


/**
*@brief �����ع�ʱ���ֵ����λΪ΢�룩
*@param[in] handle ������
*@param[in] Exposure �ع�ʱ���ֵ����λΪ΢�룩
*@return ״̬��
*@ingroup __DVP_EXPOSURE__
*@see dvpGetExposureDescr
*@see dvpGetExposure
*/
dvp2api dvpStatus dvpSetExposure(dvpHandle handle, double Exposure);


/**
*@brief ��ȡ�ع�ʱ���������Ϣ
*@param[in] handle ������
*@param[out] pExposureDescr �ع�ʱ���������Ϣ
*@return ״̬��
*@ingroup __DVP_EXPOSURE__
*@see dvpSetExposure
*@see dvpGetExposure
*/
dvp2api dvpStatus dvpGetExposureDescr(dvpHandle handle, dvpDoubleDescr *pExposureDescr);


/**
*@brief ��ȡ�Զ��ع�Ŀ�����ȵ�ֵ
*@param[in] handle ������
*@param[out] pAeTarget �Զ��ع�Ŀ�����ȵ�ֵ
*@return ״̬��
*@ingroup __DVP_EXPOSURE__
*@see dvpGetAeTargetDescr
*@see dvpSetAeTarget
*/
dvp2api dvpStatus dvpGetAeTarget(dvpHandle handle, dvpInt32 *pAeTarget);


/**
*@brief �����Զ��ع�Ŀ�����ȵ�ֵ
*@param[in] handle ������
*@param[in] AeTarget �Զ��ع�Ŀ�����ȵ�ֵ
*@return ״̬��
*@ingroup __DVP_EXPOSURE__
*@see dvpGetAeTargetDescr
*@see dvpGetAeTarget
*/
dvp2api dvpStatus dvpSetAeTarget(dvpHandle handle, dvpInt32 AeTarget);


/**
*@brief ��ȡ�Զ��ع�Ŀ�����ȵ�������Ϣ
*@param[in] handle ������
*@param[out] pAeTargetDescr �Զ��ع�Ŀ�����ȵ�������Ϣ
*@return ״̬��
*@ingroup __DVP_EXPOSURE__
*@see dvpSetAeTarget
*@see dvpGetAeTarget
*/
dvp2api dvpStatus dvpGetAeTargetDescr(dvpHandle handle, dvpIntDescr *pAeTargetDescr);


/**
*@brief ��ȡģ�������ֵ
*@param[in] handle ������
*@param[out] pAnalogGain ģ�������ֵ
*@return ״̬��
*@ingroup __DVP_EXPOSURE__
*@see dvpGetAnalogGainDescr
*@see dvpSetAnalogGain
*/
dvp2api dvpStatus dvpGetAnalogGain(dvpHandle handle, float *pAnalogGain);


/**
*@brief ����ģ�������ֵ
*@param[in] handle ������
*@param[in] AnalogGain ģ�������ֵ
*@return ״̬��
*@ingroup __DVP_EXPOSURE__
*@see dvpGetAnalogGainDescr
*@see dvpGetAnalogGain
*/
dvp2api dvpStatus dvpSetAnalogGain(dvpHandle handle, float AnalogGain);


/**
*@brief ��ȡģ�������������Ϣ
*@param[in] handle ������
*@param[out] pAnalogGainDescr ģ�������������Ϣ
*@return ״̬��
*@ingroup __DVP_EXPOSURE__
*@see dvpSetAnalogGain
*@see dvpGetAnalogGain
*/
dvp2api dvpStatus dvpGetAnalogGainDescr(dvpHandle handle, dvpFloatDescr *pAnalogGainDescr);


/**
*@brief ��ȡ�ⲿ�����ź�����ʱ���ֵ����λΪ΢�룩
*@param[in] handle ������
*@param[out] pTriggerJitterFilter �ⲿ�����ź�����ʱ���ֵ����λΪ΢�룩
*@return ״̬��
*@ingroup __DVP_TRIGGER__
*@see dvpGetTriggerJitterFilterDescr
*@see dvpSetTriggerJitterFilter
*/
dvp2api dvpStatus dvpGetTriggerJitterFilter(dvpHandle handle, double *pTriggerJitterFilter);


/**
*@brief �����ⲿ�����ź�����ʱ���ֵ����λΪ΢�룩
*@param[in] handle ������
*@param[in] TriggerJitterFilter �ⲿ�����ź�����ʱ���ֵ����λΪ΢�룩
*@return ״̬��
*@ingroup __DVP_TRIGGER__
*@see dvpGetTriggerJitterFilterDescr
*@see dvpGetTriggerJitterFilter
*/
dvp2api dvpStatus dvpSetTriggerJitterFilter(dvpHandle handle, double TriggerJitterFilter);


/**
*@brief ��ȡ�ⲿ�����ź�����ʱ���������Ϣ
*@param[in] handle ������
*@param[out] pTriggerJitterFilterDescr �ⲿ�����ź�����ʱ���������Ϣ
*@return ״̬��
*@ingroup __DVP_TRIGGER__
*@see dvpSetTriggerJitterFilter
*@see dvpGetTriggerJitterFilter
*/
dvp2api dvpStatus dvpGetTriggerJitterFilterDescr(dvpHandle handle, dvpDoubleDescr *pTriggerJitterFilterDescr);


/**
*@brief ��ȡ������ʱ��ֵ����λΪ΢�룩
*@param[in] handle ������
*@param[out] pTriggerDelay ������ʱ��ֵ����λΪ΢�룩
*@return ״̬��
*@ingroup __DVP_TRIGGER__
*@see dvpGetTriggerDelayDescr
*@see dvpSetTriggerDelay
*/
dvp2api dvpStatus dvpGetTriggerDelay(dvpHandle handle, double *pTriggerDelay);


/**
*@brief ���ô�����ʱ��ֵ����λΪ΢�룩
*@param[in] handle ������
*@param[in] TriggerDelay ������ʱ��ֵ����λΪ΢�룩
*@return ״̬��
*@ingroup __DVP_TRIGGER__
*@see dvpGetTriggerDelayDescr
*@see dvpGetTriggerDelay
*/
dvp2api dvpStatus dvpSetTriggerDelay(dvpHandle handle, double TriggerDelay);


/**
*@brief ��ȡ������ʱ��������Ϣ
*@param[in] handle ������
*@param[out] pTriggerDelayDescr ������ʱ��������Ϣ
*@return ״̬��
*@ingroup __DVP_TRIGGER__
*@see dvpSetTriggerDelay
*@see dvpGetTriggerDelay
*/
dvp2api dvpStatus dvpGetTriggerDelayDescr(dvpHandle handle, dvpDoubleDescr *pTriggerDelayDescr);


/**
*@brief ��ȡStrobe�źŵ���ʱ��ֵ����λΪ΢�룩
*@param[in] handle ������
*@param[out] pStrobeDelay Strobe�źŵ���ʱ��ֵ����λΪ΢�룩
*@return ״̬��
*@ingroup __DVP_TRIGGER__
*@see dvpGetStrobeDelayDescr
*@see dvpSetStrobeDelay
*/
dvp2api dvpStatus dvpGetStrobeDelay(dvpHandle handle, double *pStrobeDelay);


/**
*@brief ����Strobe�źŵ���ʱ��ֵ����λΪ΢�룩
*@param[in] handle ������
*@param[in] StrobeDelay Strobe�źŵ���ʱ��ֵ����λΪ΢�룩
*@return ״̬��
*@ingroup __DVP_TRIGGER__
*@see dvpGetStrobeDelayDescr
*@see dvpGetStrobeDelay
*/
dvp2api dvpStatus dvpSetStrobeDelay(dvpHandle handle, double StrobeDelay);


/**
*@brief ��ȡStrobe�źŵ���ʱ��������Ϣ
*@param[in] handle ������
*@param[out] pStrobeDelayDescr Strobe�źŵ���ʱ��������Ϣ
*@return ״̬��
*@ingroup __DVP_TRIGGER__
*@see dvpSetStrobeDelay
*@see dvpGetStrobeDelay
*/
dvp2api dvpStatus dvpGetStrobeDelayDescr(dvpHandle handle, dvpDoubleDescr *pStrobeDelayDescr);


/**
*@brief ��ȡStrobe�źŵĳ���ʱ���ֵ����λΪ΢�룩
*@param[in] handle ������
*@param[out] pStrobeDuration Strobe�źŵĳ���ʱ���ֵ����λΪ΢�룩
*@return ״̬��
*@ingroup __DVP_TRIGGER__
*@see dvpGetStrobeDurationDescr
*@see dvpSetStrobeDuration
*/
dvp2api dvpStatus dvpGetStrobeDuration(dvpHandle handle, double *pStrobeDuration);


/**
*@brief ����Strobe�źŵĳ���ʱ���ֵ����λΪ΢�룩
*@param[in] handle ������
*@param[in] StrobeDuration Strobe�źŵĳ���ʱ���ֵ����λΪ΢�룩
*@return ״̬��
*@ingroup __DVP_TRIGGER__
*@see dvpGetStrobeDurationDescr
*@see dvpGetStrobeDuration
*/
dvp2api dvpStatus dvpSetStrobeDuration(dvpHandle handle, double StrobeDuration);


/**
*@brief ��ȡStrobe�źŵĳ���ʱ���������Ϣ
*@param[in] handle ������
*@param[out] pStrobeDurationDescr Strobe�źŵĳ���ʱ���������Ϣ
*@return ״̬��
*@ingroup __DVP_TRIGGER__
*@see dvpSetStrobeDuration
*@see dvpGetStrobeDuration
*/
dvp2api dvpStatus dvpGetStrobeDurationDescr(dvpHandle handle, dvpDoubleDescr *pStrobeDurationDescr);


/**
*@brief ��ȡ���δ��������֡��
*@param[in] handle ������
*@param[out] pFramesPerTrigger ���δ��������֡��
*@return ״̬��
*@ingroup __DVP_TRIGGER__
*@see dvpGetFramesPerTriggerDescr
*@see dvpSetFramesPerTrigger
*/
dvp2api dvpStatus dvpGetFramesPerTrigger(dvpHandle handle, dvpInt32 *pFramesPerTrigger);


/**
*@brief ���õ��δ��������֡��
*@param[in] handle ������
*@param[in] FramesPerTrigger ���δ��������֡��
*@return ״̬��
*@ingroup __DVP_TRIGGER__
*@see dvpGetFramesPerTriggerDescr
*@see dvpGetFramesPerTrigger
*/
dvp2api dvpStatus dvpSetFramesPerTrigger(dvpHandle handle, dvpInt32 FramesPerTrigger);


/**
*@brief ��ȡ���δ��������֡����������Ϣ
*@param[in] handle ������
*@param[out] pFramesPerTriggerDescr ���δ��������֡����������Ϣ
*@return ״̬��
*@ingroup __DVP_TRIGGER__
*@see dvpSetFramesPerTrigger
*@see dvpGetFramesPerTrigger
*/
dvp2api dvpStatus dvpGetFramesPerTriggerDescr(dvpHandle handle, dvpIntDescr *pFramesPerTriggerDescr);


/**
*@brief ��ȡ�豸�м�ʱ����ֵ����λΪ΢�룩
*@param[in] handle ������
*@param[out] pTimerValue �豸�м�ʱ����ֵ����λΪ΢�룩
*@return ״̬��
*@ingroup __DVP_EXPOSURE__
*@see dvpGetTimerValueDescr
*@see dvpSetTimerValue
*/
dvp2api dvpStatus dvpGetTimerValue(dvpHandle handle, double *pTimerValue);


/**
*@brief �����豸�м�ʱ����ֵ����λΪ΢�룩
*@param[in] handle ������
*@param[in] TimerValue �豸�м�ʱ����ֵ����λΪ΢�룩
*@return ״̬��
*@ingroup __DVP_EXPOSURE__
*@see dvpGetTimerValueDescr
*@see dvpGetTimerValue
*/
dvp2api dvpStatus dvpSetTimerValue(dvpHandle handle, double TimerValue);


/**
*@brief ��ȡ�豸�м�ʱ����������Ϣ
*@param[in] handle ������
*@param[out] pTimerValueDescr �豸�м�ʱ����������Ϣ
*@return ״̬��
*@ingroup __DVP_EXPOSURE__
*@see dvpSetTimerValue
*@see dvpGetTimerValue
*/
dvp2api dvpStatus dvpGetTimerValueDescr(dvpHandle handle, dvpDoubleDescr *pTimerValueDescr);


/**
*@brief ��ȡ��Ƶ��״̬
*@param[in] handle ������
*@param[out] pStreamState ��Ƶ��״̬
*@return ״̬��
*@ingroup __DVP_ADVANCED__
*@see dvpSetStreamState
*/
dvp2api dvpStatus dvpGetStreamState(dvpHandle handle, dvpStreamState *pStreamState);


/**
*@brief ������Ƶ��״̬
*@param[in] handle ������
*@param[in] StreamState ��Ƶ��״̬
*@return ״̬��
*@ingroup __DVP_ADVANCED__
*@see dvpGetStreamState
*/
dvp2api dvpStatus dvpSetStreamState(dvpHandle handle, dvpStreamState StreamState);


/**
*@brief ��ȡ����ģʽ��ʹ��״̬
*@param[in] handle ������
*@param[out] pTriggerState ����ģʽ��ʹ��״̬
*@return ״̬��
*@ingroup __DVP_TRIGGER__
*@see dvpSetTriggerState
*/
dvp2api dvpStatus dvpGetTriggerState(dvpHandle handle, bool *pTriggerState);


/**
*@brief ���ô���ģʽ��ʹ��״̬
*@param[in] handle ������
*@param[in] TriggerState ����ģʽ��ʹ��״̬
*@return ״̬��
*@ingroup __DVP_TRIGGER__
*@see dvpGetTriggerState
*/
dvp2api dvpStatus dvpSetTriggerState(dvpHandle handle, bool TriggerState);


/**
*@brief ��ȡȥɫ��ʹ��״̬
*@param[in] handle ������
*@param[out] pMonoState ȥɫ��ʹ��״̬
*@return ״̬��
*@ingroup __DVP_ENHANCE__
*@see dvpSetMonoState
*/
dvp2api dvpStatus dvpGetMonoState(dvpHandle handle, bool *pMonoState);


/**
*@brief ����ȥɫ��ʹ��״̬
*@param[in] handle ������
*@param[in] MonoState ȥɫ��ʹ��״̬
*@return ״̬��
*@ingroup __DVP_ENHANCE__
*@see dvpGetMonoState
*/
dvp2api dvpStatus dvpSetMonoState(dvpHandle handle, bool MonoState);


/**
*@brief ��ȡ��Ƭ��ʹ��״̬
*@param[in] handle ������
*@param[out] pInverseState ��Ƭ��ʹ��״̬
*@return ״̬��
*@ingroup __DVP_ENHANCE__
*@see dvpSetInverseState
*/
dvp2api dvpStatus dvpGetInverseState(dvpHandle handle, bool *pInverseState);


/**
*@brief ���ø�Ƭ��ʹ��״̬
*@param[in] handle ������
*@param[in] InverseState ��Ƭ��ʹ��״̬
*@return ״̬��
*@ingroup __DVP_ENHANCE__
*@see dvpGetInverseState
*/
dvp2api dvpStatus dvpSetInverseState(dvpHandle handle, bool InverseState);


/**
*@brief ��ȡ����ת��ʹ��״̬
*@param[in] handle ������
*@param[out] pFlipHorizontalState ����ת��ʹ��״̬
*@return ״̬��
*@ingroup __DVP_ENHANCE__
*@see dvpSetFlipHorizontalState
*/
dvp2api dvpStatus dvpGetFlipHorizontalState(dvpHandle handle, bool *pFlipHorizontalState);


/**
*@brief ���ú���ת��ʹ��״̬
*@param[in] handle ������
*@param[in] FlipHorizontalState ����ת��ʹ��״̬
*@return ״̬��
*@ingroup __DVP_ENHANCE__
*@see dvpGetFlipHorizontalState
*/
dvp2api dvpStatus dvpSetFlipHorizontalState(dvpHandle handle, bool FlipHorizontalState);


/**
*@brief ��ȡ����ת��ʹ��״̬
*@param[in] handle ������
*@param[out] pFlipVerticalState ����ת��ʹ��״̬
*@return ״̬��
*@ingroup __DVP_ENHANCE__
*@see dvpSetFlipVerticalState
*/
dvp2api dvpStatus dvpGetFlipVerticalState(dvpHandle handle, bool *pFlipVerticalState);


/**
*@brief ��������ת��ʹ��״̬
*@param[in] handle ������
*@param[in] FlipVerticalState ����ת��ʹ��״̬
*@return ״̬��
*@ingroup __DVP_ENHANCE__
*@see dvpGetFlipVerticalState
*/
dvp2api dvpStatus dvpSetFlipVerticalState(dvpHandle handle, bool FlipVerticalState);


/**
*@brief ��ȡ�Զ��ع�ͳ������
*@param[in] handle ������
*@param[out] pAeRoi �Զ��ع�ͳ������
*@return ״̬��
*@ingroup __DVP_EXPOSURE__
*@see dvpSetAeRoi
*/
dvp2api dvpStatus dvpGetAeRoi(dvpHandle handle, dvpRegion *pAeRoi);


/**
*@brief �����Զ��ع�ͳ������
*@param[in] handle ������
*@param[in] AeRoi �Զ��ع�ͳ������
*@return ״̬��
*@ingroup __DVP_EXPOSURE__
*@see dvpGetAeRoi
*/
dvp2api dvpStatus dvpSetAeRoi(dvpHandle handle, dvpRegion AeRoi);


/**
*@brief ��ȡ�Զ���ƽ��ͳ������
*@param[in] handle ������
*@param[out] pAwbRoi �Զ���ƽ��ͳ������
*@return ״̬��
*@ingroup __DVP_COLOR__
*@see dvpSetAwbRoi
*/
dvp2api dvpStatus dvpGetAwbRoi(dvpHandle handle, dvpRegion *pAwbRoi);


/**
*@brief �����Զ���ƽ��ͳ������
*@param[in] handle ������
*@param[in] AwbRoi �Զ���ƽ��ͳ������
*@return ״̬��
*@ingroup __DVP_COLOR__
*@see dvpGetAwbRoi
*/
dvp2api dvpStatus dvpSetAwbRoi(dvpHandle handle, dvpRegion AwbRoi);


/**
*@brief ��ȡ�Զ��ع�ģʽ
*@param[in] handle ������
*@param[out] pAeMode �Զ��ع�ģʽ
*@return ״̬��
*@ingroup __DVP_EXPOSURE__
*@see dvpSetAeMode
*/
dvp2api dvpStatus dvpGetAeMode(dvpHandle handle, dvpAeMode *pAeMode);


/**
*@brief �����Զ��ع�ģʽ
*@param[in] handle ������
*@param[in] AeMode �Զ��ع�ģʽ
*@return ״̬��
*@ingroup __DVP_EXPOSURE__
*@see dvpGetAeMode
*/
dvp2api dvpStatus dvpSetAeMode(dvpHandle handle, dvpAeMode AeMode);


/**
*@brief ��ȡ��Ƶ��״̬
*@param[in] handle ������
*@param[out] pAntiFlick ��Ƶ��״̬
*@return ״̬��
*@ingroup __DVP_EXPOSURE__
*@see dvpSetAntiFlick
*/
dvp2api dvpStatus dvpGetAntiFlick(dvpHandle handle, dvpAntiFlick *pAntiFlick);


/**
*@brief ���ÿ�Ƶ��״̬
*@param[in] handle ������
*@param[in] AntiFlick ��Ƶ��״̬
*@return ״̬��
*@ingroup __DVP_EXPOSURE__
*@see dvpGetAntiFlick
*/
dvp2api dvpStatus dvpSetAntiFlick(dvpHandle handle, dvpAntiFlick AntiFlick);


/**
*@brief ��ȡ�Զ��ع�Ĳ�����ʽ
*@param[in] handle ������
*@param[out] pAeOperation �Զ��ع�Ĳ�����ʽ
*@return ״̬��
*@ingroup __DVP_EXPOSURE__
*@see dvpSetAeOperation
*/
dvp2api dvpStatus dvpGetAeOperation(dvpHandle handle, dvpAeOperation *pAeOperation);


/**
*@brief �����Զ��ع�Ĳ�����ʽ
*@param[in] handle ������
*@param[in] AeOperation �Զ��ع�Ĳ�����ʽ
*@return ״̬��
*@ingroup __DVP_EXPOSURE__
*@see dvpGetAeOperation
*/
dvp2api dvpStatus dvpSetAeOperation(dvpHandle handle, dvpAeOperation AeOperation);


/**
*@brief ��ȡ�Զ���ƽ��Ĳ�����ʽ
*@param[in] handle ������
*@param[out] pAwbOperation �Զ���ƽ��Ĳ�����ʽ
*@return ״̬��
*@ingroup __DVP_COLOR__
*@see dvpSetAwbOperation
*/
dvp2api dvpStatus dvpGetAwbOperation(dvpHandle handle, dvpAwbOperation *pAwbOperation);


/**
*@brief �����Զ���ƽ��Ĳ�����ʽ
*@param[in] handle ������
*@param[in] AwbOperation �Զ���ƽ��Ĳ�����ʽ
*@return ״̬��
*@ingroup __DVP_COLOR__
*@see dvpGetAwbOperation
*/
dvp2api dvpStatus dvpSetAwbOperation(dvpHandle handle, dvpAwbOperation AwbOperation);


/**
*@brief ��ȡStrobe�ź�������ʽ
*@param[in] handle ������
*@param[out] pStrobeDriver Strobe�ź�������ʽ
*@return ״̬��
*@ingroup __DVP_TRIGGER__
*@see dvpSetStrobeDriver
*/
dvp2api dvpStatus dvpGetStrobeDriver(dvpHandle handle, dvpStrobeDriver *pStrobeDriver);


/**
*@brief ����Strobe�ź�������ʽ
*@param[in] handle ������
*@param[in] StrobeDriver Strobe�ź�������ʽ
*@return ״̬��
*@ingroup __DVP_TRIGGER__
*@see dvpGetStrobeDriver
*/
dvp2api dvpStatus dvpSetStrobeDriver(dvpHandle handle, dvpStrobeDriver StrobeDriver);


/**
*@brief ��ȡStrobe�ź�����
*@param[in] handle ������
*@param[out] pStrobeOutputType Strobe�ź�����
*@return ״̬��
*@ingroup __DVP_TRIGGER__
*@see dvpSetStrobeOutputType
*/
dvp2api dvpStatus dvpGetStrobeOutputType(dvpHandle handle, dvpStrobeOutputType *pStrobeOutputType);


/**
*@brief ����Strobe�ź�����
*@param[in] handle ������
*@param[in] StrobeOutputType Strobe�ź�����
*@return ״̬��
*@ingroup __DVP_TRIGGER__
*@see dvpGetStrobeOutputType
*/
dvp2api dvpStatus dvpSetStrobeOutputType(dvpHandle handle, dvpStrobeOutputType StrobeOutputType);


/**
*@brief ��ȡ���������ź�����
*@param[in] handle ������
*@param[out] pTriggerInputType ���������ź�����
*@return ״̬��
*@ingroup __DVP_TRIGGER__
*@see dvpSetTriggerInputType
*/
dvp2api dvpStatus dvpGetTriggerInputType(dvpHandle handle, dvpTriggerInputType *pTriggerInputType);


/**
*@brief ���ô��������ź�����
*@param[in] handle ������
*@param[in] TriggerInputType ���������ź�����
*@return ״̬��
*@ingroup __DVP_TRIGGER__
*@see dvpGetTriggerInputType
*/
dvp2api dvpStatus dvpSetTriggerInputType(dvpHandle handle, dvpTriggerInputType TriggerInputType);


/**
*@brief ��ȡԴͼ���ʽ
*@param[in] handle ������
*@param[out] pSourceFormat Դͼ���ʽ
*@return ״̬��
*@ingroup __DVP_ENHANCE__
*@see dvpSetSourceFormat
*/
dvp2api dvpStatus dvpGetSourceFormat(dvpHandle handle, dvpStreamFormat *pSourceFormat);


/**
*@brief ����Դͼ���ʽ
*@param[in] handle ������
*@param[in] SourceFormat Դͼ���ʽ
*@return ״̬��
*@ingroup __DVP_ENHANCE__
*@see dvpGetSourceFormat
*/
dvp2api dvpStatus dvpSetSourceFormat(dvpHandle handle, dvpStreamFormat SourceFormat);


/**
*@brief ��ȡĿ��ͼ���ʽ
*@param[in] handle ������
*@param[out] pTargetFormat Ŀ��ͼ���ʽ
*@return ״̬��
*@ingroup __DVP_ENHANCE__
*@see dvpSetTargetFormat
*/
dvp2api dvpStatus dvpGetTargetFormat(dvpHandle handle, dvpStreamFormat *pTargetFormat);


/**
*@brief ����Ŀ��ͼ���ʽ
*@param[in] handle ������
*@param[in] TargetFormat Ŀ��ͼ���ʽ
*@return ״̬��
*@ingroup __DVP_ENHANCE__
*@see dvpGetTargetFormat
*/
dvp2api dvpStatus dvpSetTargetFormat(dvpHandle handle, dvpStreamFormat TargetFormat);


/**
*@brief ��ȡ�û���ɫ����
*@param[in] handle ������
*@param[out] pUserColorMatrix �û���ɫ����
*@return ״̬��
*@ingroup __DVP_COLOR__
*@see dvpSetUserColorMatrix
*/
dvp2api dvpStatus dvpGetUserColorMatrix(dvpHandle handle, dvpColorMatrix *pUserColorMatrix);


/**
*@brief �����û���ɫ����
*@param[in] handle ������
*@param[in] UserColorMatrix �û���ɫ����
*@return ״̬��
*@ingroup __DVP_COLOR__
*@see dvpGetUserColorMatrix
*/
dvp2api dvpStatus dvpSetUserColorMatrix(dvpHandle handle, dvpColorMatrix UserColorMatrix);


/**
*@brief ��ȡ���ӳ�ʱʱ���ֵ ����λΪ���룩
*@param[in] handle ������
*@param[out] pLinkTimeout ���ӳ�ʱʱ���ֵ ����λΪ���룩
*@return ״̬��
*@ingroup __DVP_ADVANCED__
*@see dvpSetLinkTimeout
*/
dvp2api dvpStatus dvpGetLinkTimeout(dvpHandle handle, dvpUint32 *pLinkTimeout);


/**
*@brief �������ӳ�ʱʱ���ֵ ����λΪ���룩
*@param[in] handle ������
*@param[in] LinkTimeout ���ӳ�ʱʱ���ֵ ����λΪ���룩
*@return ״̬��
*@ingroup __DVP_ADVANCED__
*@see dvpGetLinkTimeout
*/
dvp2api dvpStatus dvpSetLinkTimeout(dvpHandle handle, dvpUint32 LinkTimeout);


/**
*@brief ��ȡ����IO�ĵ�ƽ״̬
*@param[in] handle ������
*@param[in] inputIo ����IO
*@param[out] pInputIoLevel ����IO�ĵ�ƽ״̬
*@return ״̬��
*@ingroup __DVP_TRIGGER__
*/
dvp2api dvpStatus dvpGetInputIoLevel(dvpHandle handle, dvpInputIo inputIo, bool *pInputIoLevel);


/**
*@brief ��ȡ���IO�ĵ�ƽ״̬
*@param[in] handle ������
*@param[in] outputIo ���IO
*@param[out] pOutputIoLevel ���IO�ĵ�ƽ״̬
*@return ״̬��
*@ingroup __DVP_TRIGGER__
*@see dvpSetOutputIoLevel
*/
dvp2api dvpStatus dvpGetOutputIoLevel(dvpHandle handle, dvpOutputIo outputIo, bool *pOutputIoLevel);


/**
*@brief ��ȡ���IO�ĵ�ƽ״̬
*@param[in] handle ������
*@param[in] outputIo ���IO
*@param[in] OutputIoLevel ���IO�ĵ�ƽ״̬
*@return ״̬��
*@ingroup __DVP_TRIGGER__
*@see dvpGetOutputIoLevel
*/
dvp2api dvpStatus dvpSetOutputIoLevel(dvpHandle handle, dvpOutputIo outputIo, bool OutputIoLevel);


/**
*@brief ��ȡ���IO�Ĺ�������
*@param[in] handle ������
*@param[in] outputIo ���IO
*@param[out] pOutputIoFunction ���IO�Ĺ�������
*@return ״̬��
*@ingroup __DVP_TRIGGER__
*@see dvpSetOutputIoFunction
*/
dvp2api dvpStatus dvpGetOutputIoFunction(dvpHandle handle, dvpOutputIo outputIo, dvpOutputIoFunction *pOutputIoFunction);


/**
*@brief ��ȡ���IO�Ĺ�������
*@param[in] handle ������
*@param[in] outputIo ���IO
*@param[in] OutputIoFunction ���IO�Ĺ�������
*@return ״̬��
*@ingroup __DVP_TRIGGER__
*@see dvpGetOutputIoFunction
*/
dvp2api dvpStatus dvpSetOutputIoFunction(dvpHandle handle, dvpOutputIo outputIo, dvpOutputIoFunction OutputIoFunction);


/**
*@brief ��ȡ����IO�Ĺ�������
*@param[in] handle ������
*@param[in] inputIo ����IO
*@param[out] pInputIoFunction ����IO�Ĺ�������
*@return ״̬��
*@ingroup __DVP_TRIGGER__
*@see dvpSetInputIoFunction
*/
dvp2api dvpStatus dvpGetInputIoFunction(dvpHandle handle, dvpInputIo inputIo, dvpInputIoFunction *pInputIoFunction);


/**
*@brief ��ȡ����IO�Ĺ�������
*@param[in] handle ������
*@param[in] inputIo ����IO
*@param[in] InputIoFunction ����IO�Ĺ�������
*@return ״̬��
*@ingroup __DVP_TRIGGER__
*@see dvpGetInputIoFunction
*/
dvp2api dvpStatus dvpSetInputIoFunction(dvpHandle handle, dvpInputIo inputIo, dvpInputIoFunction InputIoFunction);


/**
*@brief ��ȡ��ǰɫ�ʷ���ѡ�������
*@param[in] handle ������
*@param[out] pColorSolutionSel ��ǰɫ�ʷ���ѡ�������
*@return ״̬��
*@ingroup __DVP_ADVANCED__
*@see dvpGetColorSolutionSelDescr
*@see dvpGetColorSolutionSelDetail
*@see dvpSetColorSolutionSel
*/
dvp2api dvpStatus dvpGetColorSolutionSel(dvpHandle handle, dvpUint32 *pColorSolutionSel);


/**
*@brief ���õ�ǰɫ�ʷ���ѡ�������
*@param[in] handle ������
*@param[in] ColorSolutionSel ��ǰɫ�ʷ���ѡ�������
*@return ״̬��
*@ingroup __DVP_ADVANCED__
*@see dvpGetColorSolutionSelDescr
*@see dvpGetColorSolutionSelDetail
*@see dvpGetColorSolutionSel
*/
dvp2api dvpStatus dvpSetColorSolutionSel(dvpHandle handle, dvpUint32 ColorSolutionSel);


/**
*@brief ��ȡɫ�ʷ���ѡ��������������Ϣ
*@param[in] handle ������
*@param[out] pColorSolutionSelDescr ɫ�ʷ���ѡ��������������Ϣ
*@return ״̬��
*@ingroup __DVP_ADVANCED__
*@see dvpGetColorSolutionSel
*@see dvpGetColorSolutionSelDetail
*/
dvp2api dvpStatus dvpGetColorSolutionSelDescr(dvpHandle handle, dvpSelectionDescr *pColorSolutionSelDescr);


/**
*@brief ��ȡ��ǰɫ�ʷ���ѡ��������Ӧ�ľ�����Ϣ
*@param[in] handle ������
*@param[in] ColorSolutionSel ɫ�ʷ���������
*@param[out] pColorSolutionSelDetail ��ǰɫ�ʷ���ѡ��������Ӧ�ľ�����Ϣ
*@return ״̬��
*@ingroup __DVP_ADVANCED__
*@see dvpGetColorSolutionSel
*@see dvpGetColorSolutionSelDescr
*/
dvp2api dvpStatus dvpGetColorSolutionSelDetail(dvpHandle handle, dvpUint32 ColorSolutionSel, dvpSelection *pColorSolutionSelDetail);


/**
*@brief ��ȡ��ǰBayerתRGB�����㷨ѡ�������
*@param[in] handle ������
*@param[out] pBayerDecodeSel ��ǰBayerתRGB�����㷨ѡ�������
*@return ״̬��
*@ingroup __DVP_ADVANCED__
*@see dvpGetBayerDecodeSelDescr
*@see dvpGetBayerDecodeSelDetail
*@see dvpSetBayerDecodeSel
*/
dvp2api dvpStatus dvpGetBayerDecodeSel(dvpHandle handle, dvpUint32 *pBayerDecodeSel);


/**
*@brief ���õ�ǰBayerתRGB�����㷨ѡ�������
*@param[in] handle ������
*@param[in] BayerDecodeSel ��ǰBayerתRGB�����㷨ѡ�������
*@return ״̬��
*@ingroup __DVP_ADVANCED__
*@see dvpGetBayerDecodeSelDescr
*@see dvpGetBayerDecodeSelDetail
*@see dvpGetBayerDecodeSel
*/
dvp2api dvpStatus dvpSetBayerDecodeSel(dvpHandle handle, dvpUint32 BayerDecodeSel);


/**
*@brief ��ȡBayerתRGB�����㷨ѡ��������������Ϣ
*@param[in] handle ������
*@param[out] pBayerDecodeSelDescr BayerתRGB�����㷨ѡ��������������Ϣ
*@return ״̬��
*@ingroup __DVP_ADVANCED__
*@see dvpGetBayerDecodeSel
*@see dvpGetBayerDecodeSelDetail
*/
dvp2api dvpStatus dvpGetBayerDecodeSelDescr(dvpHandle handle, dvpSelectionDescr *pBayerDecodeSelDescr);


/**
*@brief ��ȡ��ǰBayerתRGB�����㷨ѡ��������Ӧ�ľ�����Ϣ
*@param[in] handle ������
*@param[in] BayerDecodeSel BayerתRGB�����㷨������
*@param[out] pBayerDecodeSelDetail ��ǰBayerתRGB�����㷨ѡ��������Ӧ�ľ�����Ϣ
*@return ״̬��
*@ingroup __DVP_ADVANCED__
*@see dvpGetBayerDecodeSel
*@see dvpGetBayerDecodeSelDescr
*/
dvp2api dvpStatus dvpGetBayerDecodeSelDetail(dvpHandle handle, dvpUint32 BayerDecodeSel, dvpSelection *pBayerDecodeSelDetail);


/**
*@brief ��ȡ��ǰ�ֱ���ģʽѡ�������
*@param[in] handle ������
*@param[out] pResolutionModeSel ��ǰ�ֱ���ģʽѡ�������
*@return ״̬��
*@ingroup __DVP_SIZE__
*@see dvpGetResolutionModeSelDescr
*@see dvpGetResolutionModeSelDetail
*@see dvpSetResolutionModeSel
*/
dvp2api dvpStatus dvpGetResolutionModeSel(dvpHandle handle, dvpUint32 *pResolutionModeSel);


/**
*@brief ���õ�ǰ�ֱ���ģʽѡ�������
*@param[in] handle ������
*@param[in] ResolutionModeSel ��ǰ�ֱ���ģʽѡ�������
*@return ״̬��
*@ingroup __DVP_SIZE__
*@see dvpGetResolutionModeSelDescr
*@see dvpGetResolutionModeSelDetail
*@see dvpGetResolutionModeSel
*/
dvp2api dvpStatus dvpSetResolutionModeSel(dvpHandle handle, dvpUint32 ResolutionModeSel);


/**
*@brief ��ȡ�ֱ���ģʽѡ��������������Ϣ
*@param[in] handle ������
*@param[out] pResolutionModeSelDescr �ֱ���ģʽѡ��������������Ϣ
*@return ״̬��
*@ingroup __DVP_SIZE__
*@see dvpGetResolutionModeSel
*@see dvpGetResolutionModeSelDetail
*/
dvp2api dvpStatus dvpGetResolutionModeSelDescr(dvpHandle handle, dvpSelectionDescr *pResolutionModeSelDescr);


/**
*@brief ��ȡ��ǰ�ֱ���ģʽѡ��������Ӧ�ľ�����Ϣ
*@param[in] handle ������
*@param[in] ResolutionModeSel �ֱ���ģʽ������
*@param[out] pResolutionModeSelDetail ��ǰ�ֱ���ģʽѡ��������Ӧ�ľ�����Ϣ
*@return ״̬��
*@ingroup __DVP_SIZE__
*@see dvpGetResolutionModeSel
*@see dvpGetResolutionModeSelDescr
*/
dvp2api dvpStatus dvpGetResolutionModeSelDetail(dvpHandle handle, dvpUint32 ResolutionModeSel, dvpResolutionMode *pResolutionModeSelDetail);


/**
*@brief ��ȡ��ǰ�Զ��عⷽ��ѡ�������
*@param[in] handle ������
*@param[out] pAeSchemeSel ��ǰ�Զ��عⷽ��ѡ�������
*@return ״̬��
*@ingroup __DVP_ADVANCED__
*@see dvpGetAeSchemeSelDescr
*@see dvpGetAeSchemeSelDetail
*@see dvpSetAeSchemeSel
*/
dvp2api dvpStatus dvpGetAeSchemeSel(dvpHandle handle, dvpUint32 *pAeSchemeSel);


/**
*@brief ���õ�ǰ�Զ��عⷽ��ѡ�������
*@param[in] handle ������
*@param[in] AeSchemeSel ��ǰ�Զ��عⷽ��ѡ�������
*@return ״̬��
*@ingroup __DVP_ADVANCED__
*@see dvpGetAeSchemeSelDescr
*@see dvpGetAeSchemeSelDetail
*@see dvpGetAeSchemeSel
*/
dvp2api dvpStatus dvpSetAeSchemeSel(dvpHandle handle, dvpUint32 AeSchemeSel);


/**
*@brief ��ȡ�Զ��عⷽ��ѡ��������������Ϣ
*@param[in] handle ������
*@param[out] pAeSchemeSelDescr �Զ��عⷽ��ѡ��������������Ϣ
*@return ״̬��
*@ingroup __DVP_ADVANCED__
*@see dvpGetAeSchemeSel
*@see dvpGetAeSchemeSelDetail
*/
dvp2api dvpStatus dvpGetAeSchemeSelDescr(dvpHandle handle, dvpSelectionDescr *pAeSchemeSelDescr);


/**
*@brief ��ȡ��ǰ�Զ��عⷽ��ѡ��������Ӧ�ľ�����Ϣ
*@param[in] handle ������
*@param[in] AeSchemeSel �Զ��عⷽ��������
*@param[out] pAeSchemeSelDetail ��ǰ�Զ��عⷽ��ѡ��������Ӧ�ľ�����Ϣ
*@return ״̬��
*@ingroup __DVP_ADVANCED__
*@see dvpGetAeSchemeSel
*@see dvpGetAeSchemeSelDescr
*/
dvp2api dvpStatus dvpGetAeSchemeSelDetail(dvpHandle handle, dvpUint32 AeSchemeSel, dvpSelection *pAeSchemeSelDetail);


/**
*@brief ��ȡ��ǰ����Roiѡ�������
*@param[in] handle ������
*@param[out] pQuickRoiSel ��ǰ����Roiѡ�������
*@return ״̬��
*@ingroup __DVP_SIZE__
*@see dvpGetQuickRoiSelDescr
*@see dvpGetQuickRoiSelDetail
*@see dvpSetQuickRoiSel
*/
dvp2api dvpStatus dvpGetQuickRoiSel(dvpHandle handle, dvpUint32 *pQuickRoiSel);


/**
*@brief ���õ�ǰ����Roiѡ�������
*@param[in] handle ������
*@param[in] QuickRoiSel ��ǰ����Roiѡ�������
*@return ״̬��
*@ingroup __DVP_SIZE__
*@see dvpGetQuickRoiSelDescr
*@see dvpGetQuickRoiSelDetail
*@see dvpGetQuickRoiSel
*/
dvp2api dvpStatus dvpSetQuickRoiSel(dvpHandle handle, dvpUint32 QuickRoiSel);


/**
*@brief ��ȡ����Roiѡ��������������Ϣ
*@param[in] handle ������
*@param[out] pQuickRoiSelDescr ����Roiѡ��������������Ϣ
*@return ״̬��
*@ingroup __DVP_SIZE__
*@see dvpGetQuickRoiSel
*@see dvpGetQuickRoiSelDetail
*/
dvp2api dvpStatus dvpGetQuickRoiSelDescr(dvpHandle handle, dvpSelectionDescr *pQuickRoiSelDescr);


/**
*@brief ��ȡ��ǰ����Roiѡ��������Ӧ�ľ�����Ϣ
*@param[in] handle ������
*@param[in] QuickRoiSel ����Roi������
*@param[out] pQuickRoiSelDetail ��ǰ����Roiѡ��������Ӧ�ľ�����Ϣ
*@return ״̬��
*@ingroup __DVP_SIZE__
*@see dvpGetQuickRoiSel
*@see dvpGetQuickRoiSelDescr
*/
dvp2api dvpStatus dvpGetQuickRoiSelDetail(dvpHandle handle, dvpUint32 QuickRoiSel, dvpQuickRoi *pQuickRoiSelDetail);


/**
*@brief ��ȡ��ǰ���زɼ�����ѡ�������
*@param[in] handle ������
*@param[out] pPixelRateSel ��ǰ���زɼ�����ѡ�������
*@return ״̬��
*@ingroup __DVP_ADVANCED__
*@see dvpGetPixelRateSelDescr
*@see dvpGetPixelRateSelDetail
*@see dvpSetPixelRateSel
*/
dvp2api dvpStatus dvpGetPixelRateSel(dvpHandle handle, dvpUint32 *pPixelRateSel);


/**
*@brief ���õ�ǰ���زɼ�����ѡ�������
*@param[in] handle ������
*@param[in] PixelRateSel ��ǰ���زɼ�����ѡ�������
*@return ״̬��
*@ingroup __DVP_ADVANCED__
*@see dvpGetPixelRateSelDescr
*@see dvpGetPixelRateSelDetail
*@see dvpGetPixelRateSel
*/
dvp2api dvpStatus dvpSetPixelRateSel(dvpHandle handle, dvpUint32 PixelRateSel);


/**
*@brief ��ȡ���زɼ�����ѡ��������������Ϣ
*@param[in] handle ������
*@param[out] pPixelRateSelDescr ���زɼ�����ѡ��������������Ϣ
*@return ״̬��
*@ingroup __DVP_ADVANCED__
*@see dvpGetPixelRateSel
*@see dvpGetPixelRateSelDetail
*/
dvp2api dvpStatus dvpGetPixelRateSelDescr(dvpHandle handle, dvpSelectionDescr *pPixelRateSelDescr);


/**
*@brief ��ȡ��ǰ���زɼ�����ѡ��������Ӧ�ľ�����Ϣ
*@param[in] handle ������
*@param[in] PixelRateSel ���زɼ����ʵ�����
*@param[out] pPixelRateSelDetail ��ǰ���زɼ�����ѡ��������Ӧ�ľ�����Ϣ
*@return ״̬��
*@ingroup __DVP_ADVANCED__
*@see dvpGetPixelRateSel
*@see dvpGetPixelRateSelDescr
*/
dvp2api dvpStatus dvpGetPixelRateSelDetail(dvpHandle handle, dvpUint32 PixelRateSel, dvpSelection *pPixelRateSelDetail);


/**
*@brief ��ȡ��ǰ���ݴ������ѡ�������
*@param[in] handle ������
*@param[out] pPacketSizeSel ��ǰ���ݴ������ѡ�������
*@return ״̬��
*@ingroup __DVP_ADVANCED__
*@see dvpGetPacketSizeSelDescr
*@see dvpGetPacketSizeSelDetail
*@see dvpSetPacketSizeSel
*/
dvp2api dvpStatus dvpGetPacketSizeSel(dvpHandle handle, dvpUint32 *pPacketSizeSel);


/**
*@brief ���õ�ǰ���ݴ������ѡ�������
*@param[in] handle ������
*@param[in] PacketSizeSel ��ǰ���ݴ������ѡ�������
*@return ״̬��
*@ingroup __DVP_ADVANCED__
*@see dvpGetPacketSizeSelDescr
*@see dvpGetPacketSizeSelDetail
*@see dvpGetPacketSizeSel
*/
dvp2api dvpStatus dvpSetPacketSizeSel(dvpHandle handle, dvpUint32 PacketSizeSel);


/**
*@brief ��ȡ���ݴ������ѡ��������������Ϣ
*@param[in] handle ������
*@param[out] pPacketSizeSelDescr ���ݴ������ѡ��������������Ϣ
*@return ״̬��
*@ingroup __DVP_ADVANCED__
*@see dvpGetPacketSizeSel
*@see dvpGetPacketSizeSelDetail
*/
dvp2api dvpStatus dvpGetPacketSizeSelDescr(dvpHandle handle, dvpSelectionDescr *pPacketSizeSelDescr);


/**
*@brief ��ȡ��ǰ���ݴ������ѡ��������Ӧ�ľ�����Ϣ
*@param[in] handle ������
*@param[in] PacketSizeSel ���ݴ������������
*@param[out] pPacketSizeSelDetail ��ǰ���ݴ������ѡ��������Ӧ�ľ�����Ϣ
*@return ״̬��
*@ingroup __DVP_ADVANCED__
*@see dvpGetPacketSizeSel
*@see dvpGetPacketSizeSelDescr
*/
dvp2api dvpStatus dvpGetPacketSizeSelDetail(dvpHandle handle, dvpUint32 PacketSizeSel, dvpSelection *pPacketSizeSelDetail);


/**
*@brief ��ȡ��ǰӲ��������ѡ�������
*@param[in] handle ������
*@param[out] pAccelerateSel ��ǰӲ��������ѡ�������
*@return ״̬��
*@ingroup __DVP_ADVANCED__
*@see dvpGetAccelerateSelDescr
*@see dvpGetAccelerateSelDetail
*@see dvpSetAccelerateSel
*/
dvp2api dvpStatus dvpGetAccelerateSel(dvpHandle handle, dvpUint32 *pAccelerateSel);


/**
*@brief ���õ�ǰӲ��������ѡ�������
*@param[in] handle ������
*@param[in] AccelerateSel ��ǰӲ��������ѡ�������
*@return ״̬��
*@ingroup __DVP_ADVANCED__
*@see dvpGetAccelerateSelDescr
*@see dvpGetAccelerateSelDetail
*@see dvpGetAccelerateSel
*/
dvp2api dvpStatus dvpSetAccelerateSel(dvpHandle handle, dvpUint32 AccelerateSel);


/**
*@brief ��ȡӲ��������ѡ��������������Ϣ
*@param[in] handle ������
*@param[out] pAccelerateSelDescr Ӳ��������ѡ��������������Ϣ
*@return ״̬��
*@ingroup __DVP_ADVANCED__
*@see dvpGetAccelerateSel
*@see dvpGetAccelerateSelDetail
*/
dvp2api dvpStatus dvpGetAccelerateSelDescr(dvpHandle handle, dvpSelectionDescr *pAccelerateSelDescr);


/**
*@brief ��ȡ��ǰӲ��������ѡ��������Ӧ�ľ�����Ϣ
*@param[in] handle ������
*@param[in] AccelerateSel Ӳ��������������
*@param[out] pAccelerateSelDetail ��ǰӲ��������ѡ��������Ӧ�ľ�����Ϣ
*@return ״̬��
*@ingroup __DVP_ADVANCED__
*@see dvpGetAccelerateSel
*@see dvpGetAccelerateSelDescr
*/
dvp2api dvpStatus dvpGetAccelerateSelDetail(dvpHandle handle, dvpUint32 AccelerateSel, dvpSelection *pAccelerateSelDetail);


/**
*@brief ���ú�,��,����ɫ����������
*@param[in] handle ������
*@param[in] rGain ��ɫ��������
*@param[in] gGain ��ɫ��������
*@param[in] bGain ��ɫ��������
*@ingroup __DVP_COLOR__
*@see dvpGetRgbGain
*@see dvpSetRgbGainState
*@see dvpGetRgbGainState
*@see dvpGetRGainDescr
*/
dvp2api dvpStatus dvpSetRgbGain(dvpHandle handle, float rGain, float gGain, float bGain);


/**
*@brief ��ȡ��,��,����ɫ����������
*@param[in] handle ������
*@param[out] prGain ��ɫ��������
*@param[out] pgGain ��ɫ��������
*@param[out] pbGain ��ɫ��������
*@ingroup __DVP_COLOR__
*@see dvpSetRgbGain
*@see dvpSetRgbGainState
*@see dvpGetRgbGainState
*@see dvpGetRGainDescr
*/
dvp2api dvpStatus dvpGetRgbGain(dvpHandle handle, float *prGain, float *pgGain, float *pbGain);


/**
*@brief ���ú�,��,����ɫ���������湦�ܵ�ʹ��״̬
*@param[in] handle ������
*@param[in] state ��,��,����ɫ���������湦�ܵ�ʹ��״̬
*@ingroup __DVP_COLOR__
*@see dvpSetRgbGain
*@see dvpGetRgbGain
*@see dvpGetRgbGainState
*/
dvp2api dvpStatus dvpSetRgbGainState(dvpHandle handle, bool state);


/**
*@brief ��ȡ��,��,����ɫ���������湦�ܵ�ʹ��״̬
*@param[in] handle ������
*@param[out] pState ��,��,����ɫ���������湦�ܵ�ʹ��״̬
*@ingroup __DVP_COLOR__
*@see dvpSetRgbGain
*@see dvpGetRgbGain
*@see dvpSetRgbGainState
*/
dvp2api dvpStatus dvpGetRgbGainState(dvpHandle handle, bool *pState);



/** @defgroup __DVP2_API_BASE__ ��������
*@{
*/
/**
*@brief ˢ�������ӵ�����б���������������
*@param[out] pCount �������
*@see dvpEnum
*@see dvpOpen
*@see dvpOpenByName
*@note Ӧ����@link #dvpEnum ö��@endlink��@link #dvpOpen ��@endlink���ǰִ�У�����ͬ��һ���̣߳�
*/
dvp2api dvpStatus dvpRefresh(dvpUint32 *pCount);


/**
*@brief ��������ö�������Ϣ
*@param[in] index �������
*@param[out] pCameraInfo �����Ϣ
*@see dvpGetCameraInfo
*@code
dvpUint32 count;
dvpRefresh(&count);
for (dvpUint32 i = 0; i < count; i++)
{
    dvpCameraInfo info;
    if(dvpEnum(i, &info) == DVP_STATUS_OK)
    {
        printf("Camera FriendlyName : %s", info.FriendlyName);
    }
}
*@endcode
*@note Ӧ����@link #dvpRefresh ˢ��@endlink�����ִ�У�����ͬ��һ���̣߳�
*/
dvp2api dvpStatus dvpEnum(dvpUint32 index, dvpCameraInfo *pCameraInfo);


/**
*@brief ����@link #dvpCameraInfo::FriendlyName �Ѻ�����@endlink�������
*@param[in] friendlyName �Ѻ�����
*@param[in] type �򿪷�ʽ
*@param[out] pHandle ������
*@see dvpEnum
*@see dvpOpen
*@see dvpGetCameraInfo
*@note �˲������Զ�@link #dvpRefresh ˢ��@endlink�������
*@warning ������@link #dvpStreamCallback �ص�����@endlink��ʹ�ô˹���
*/
dvp2api dvpStatus dvpOpenByName(const char *friendlyName, dvpOpenMode type, dvpHandle *pHandle);


/**
*@brief ���������������
*@param[in] index �������
*@param[in] mode �򿪷�ʽ
*@param[out] pHandle ������
*@see dvpRefresh
*@see dvpEnum
*@see dvpOpenByName
*@see dvpGetCameraInfo
*@note Ӧ����@link #dvpRefresh ˢ��@endlink�����ִ�У�����ͬ��һ���̣߳�
*@warning ������@link #dvpStreamCallback �ص�����@endlink��ʹ�ô˹���
*/
dvp2api dvpStatus dvpOpen(dvpUint32 index, dvpOpenMode mode, dvpHandle *pHandle);


/**
*@brief ����������Ƿ���Ч
*@param[in] handle ������
*@param[out] pIsValid ��Ч״̬
*@note @link #dvpOpen ��@endlink�ɹ�������Ч��@link #dvpClose �ر�@endlink�ɹ�����ʧЧ
*/
dvp2api dvpStatus dvpIsValid(dvpHandle handle, bool *pIsValid);


/**
*@brief �������Ƿ�����
*@param[in] handle ������
*@param[in] pIsOnline ����״̬
*/
dvp2api dvpStatus dvpIsOnline(dvpHandle handle, bool *pIsOnline);


/**
*@brief ������Ƶ��
*@param[in] handle ������
*@see dvpOpen
*@see dvpStop
*/
dvp2api dvpStatus dvpStart(dvpHandle handle);


/**
*@brief ֹͣ��Ƶ��
*@param[in] handle ������
*@see dvpStart
*@see dvpClose
*/
dvp2api dvpStatus dvpStop(dvpHandle handle);


/**
*@brief ��ȡһ֡ͼ��
*@param[in] handle ������
*@param[out] pFrame ֡��Ϣ
*@param[out] pBuffer ͼ�����ݵ��ڴ��׵�ַ
*@param[in] timeout ��ʱʱ�䣨���룩
*@see dvpStreamCallback
*@note ����@link #dvpStart ����@endlink��Ƶ��������ʹ�ô˹���
*@warning �ɱ�������õ�ͼ�����ݻ��棬����һ�ε��ñ�����ʱ���������Ч����ˣ��ڶ��߳�ͬʱ���ͼ���Ӧ���У���Ҫ�����߳�ͬ�����ٽ�α���
*/
dvp2api dvpStatus dvpGetFrame(dvpHandle handle, dvpFrame *pFrame, void **pBuffer, dvpUint32 timeout);


/**
*@brief �ر����
*@param[in] handle ������
*@see dvpStop
*@warning ������@link #dvpStreamCallback �ص�����@endlink��ʹ�ô˹���
*@warning �ر�����������������ٿ���
*/
dvp2api dvpStatus dvpClose(dvpHandle handle);



/** @defgroup __DVP2_API_CALLBACK__ �ص�����
*@{
*/
/** @brief ��Ƶ���ص�����
*@param[in] handle ������
*@param[in] event �¼�����
*@param[in] pContext �û�ָ��
*@param[in] pFrame ֡��Ϣ
*@param[in] pBuffer ͼ������
*@see dvpRegisterStreamCallback
*@see dvpUnregisterStreamCallback
*@note �����ڻص������У�����@link #dvpDrawPicture ��ʾ@endlink��@link #dvpSavePicture �洢@endlinkͼ��
*@warning �����ڻص������У�@link #dvpOpen ��@endlink��@link #dvpClose �ر�@endlink��@link #dvpStart ����@endlink��@link #dvpStop ֹͣ@endlink������Լ�@link #dvpGetFrame ץȡͼ��@endlink  */
typedef dvpInt32(dvpStreamCallback)(dvpHandle handle, dvpStreamEvent event, void *pContext, dvpFrame *pFrame, void *pBuffer);

/**
*@brief ע����Ƶ���ص�����
*@param[in] handle ������
*@param[in] proc �ص������ĺ���ָ��
*@param[in] event �ص��������¼�����
*@param[in] pContext �ص��������û�ָ��
*@see dvpUnregisterStreamCallback
*@note �ɴ˺�����ǰ����������ͬȷ��һ���ص�����
*/
dvp2api dvpStatus dvpRegisterStreamCallback(dvpHandle handle, dvpStreamCallback proc, dvpStreamEvent event, void *pContext);


/**
*@brief ע����Ƶ���ص�����
*@param[in] handle ������
*@param[in] proc �ص������ĺ���ָ��
*@param[in] event �ص��������¼�����
*@param[in] pContext �ص��������û�ָ��
*@note ����@link #dvpRegisterStreamCallback ע��ص�����@endlink��ʹ�õ�ǰ��������һ�²���ע����Ӧ�Ļص�����
*/
dvp2api dvpStatus dvpUnregisterStreamCallback(dvpHandle handle, dvpStreamCallback proc, dvpStreamEvent event, void *pContext);


/** @} end of __DVP2_API_CALLBACK__ */

/** @defgroup __DVP2_API_CONFIG__ �浵����
*@{
*/
/**
*@brief ����Ĭ������
*@param[in] handle ������
*@see dvpLoadConfig
*@see dvpSaveConfig
*@warning �Ḳ�ǵ�ǰ���á����б�Ҫ��������@link #dvpSaveConfig ���ݵ�ǰ����@endlink�������ļ�
*/
dvp2api dvpStatus dvpLoadDefault(dvpHandle handle);


/**
*@brief �������ļ��м�������
*@param[in] handle ������
*@param[in] path �����ļ���·�����ļ������Զ�ѡ��·��������ָ�루�Զ�ѡ��·�����ļ�����
*@see dvpLoadDefault
*@see dvpSaveConfig
*@warning �Ḳ�ǵ�ǰ���á����б�Ҫ��������@link #dvpSaveConfig ���ݵ�ǰ����@endlink�������ļ�
*/
dvp2api dvpStatus dvpLoadConfig(dvpHandle handle, const char *path);


/**
*@brief ��ǰ���ñ��浽�����ļ�
*@param[in] handle ������
*@param[in] path �����ļ���·�����ļ������Զ�ѡ��·��������ָ�루�Զ�ѡ��·�����ļ�����
*@see dvpLoadDefault
*@see dvpLoadConfig
*@warning ��ȷ����ǰ����ӵ�жԴ��ļ���д��Ȩ��
*/
dvp2api dvpStatus dvpSaveConfig(dvpHandle handle, const char *path);


/** @} end of __DVP2_API_CONFIG__ */
/** @} end of __DVP2_API_BASE__ */

/** @defgroup __DVP2_API_EXTEND__ ʵ�ù���
*@{
*/
/**
*@brief �ڴ�������ʾͼ��
*@param[in] pFrame ֡��Ϣ
*@param[in] pBuffer ͼ�����ݵ��ڴ��׵�ַ��Ŀǰ֧�ֵ����ݸ�ʽ������RAW, RGB24�� 
*@param[in] hWnd ������ʾͼ��Ĵ��ھ��
*@param[in] sRect ������ʾ��ͼ�����򡣿�ָ���������ͼ������
*@param[in] dRect ������ʾ�Ĵ������򡣿�ָ�����������������
*@note ������@link #dvpStreamCallback �ص�����@endlink��ʹ�ô˹���
*@warning Ŀǰ��֧��RGB24��ͼ�����ݸ�ʽ
*/
dvp2api dvpStatus dvpDrawPicture(dvpFrame *pFrame, void *pBuffer, HWND hWnd, LPRECT sRect, LPRECT dRect);


/**
*@brief ��ͼ�񱣴浽�ļ�
*@param[in] pFrame ֡��Ϣ
*@param[in] pBuffer ͼ�����ݵ��ڴ��׵�ַ��Ŀǰ֧�ֵ����ݸ�ʽ������RAW, RGB24��
*@param[in] file �ļ���������·����ͼ���ļ��ĸ�ʽ���ļ�����չ����������Ŀǰ֧�ֵ�ͼ���ʽ������bmp, jpeg, png, tiff, gif, dat(��ͼ������)��
*@param[in] quality ͼ��Ʒ�ʣ�����jpeg��ʽ��Ч������ȡֵ��Χ��[1,100]
*@see dvpGetFrame
*@see dvpStreamCallback
*/
dvp2api dvpStatus dvpSavePicture(const dvpFrame *pFrame, const void *pBuffer, const char *file, dvpInt32 quality);


/**
*@brief ����¼�񣬴�����Ƶ�ļ����������Ƶ�������ľ��
*@param[in] file ��Ƶ�ļ���������·������Ƶ�ļ��ĸ�ʽ���ļ�����չ����������Ŀǰ֧�ֵ���Ƶ��ʽ������wmv, avi��
*@param[in] width ��Ƶ������
*@param[in] height ��Ƶ����߶�
*@param[in] quality ��Ƶ����Ʒ�ʣ�����avi��ʽ��Ч������ȡֵ��Χ��[1,100]
*@param[out] pHandle ��Ƶ���������
*@see dvpVideoRecordWrite
*@see dvpStopVideoRecord
*/
dvp2api dvpStatus dvpStartVideoRecord(const char *file, dvpUint32 width, dvpUint32 height, dvpInt32 quality, dvpRecordHandle *pHandle);


/**
*@brief �����Ƶ�������ľ���Ƿ���Ч
*@param[in] handle ��Ƶ���������
*@param[out] pValid ��Ч״̬
*@note @link #dvpStartVideoRecord ����¼��@endlink�ɹ�������Ч��@link #dvpStopVideoRecord ֹͣ¼��@endlink�ɹ�����ʧЧ
*/
dvp2api dvpStatus dvpIsVideoRecorderValid(dvpRecordHandle handle, bool *pValid);


/**
*@brief ����Ƶ������д����Ƶ�ļ�
*@param[in] handle ��Ƶ���������
*@param[in] pFrame ֡��Ϣ
*@param[in] pBuffer ͼ�����ݵ��ڴ��׵�ַ��Ŀǰ֧�ֵ����ݸ�ʽ������RGB24��
*@see dvpGetFrame
*@see dvpStartVideoRecord
*@see dvpStopVideoRecord
*/
dvp2api dvpStatus dvpVideoRecordWrite(dvpRecordHandle handle, dvpFrame *pFrame, void *pBuffer);


/**
*@brief ֹͣ¼�񣬹ر���Ƶ�ļ������ͷ���Ƶ�������ľ��
*@param[in] handle ��Ƶ���������
*@see dvpVideoRecordWrite
*@see dvpStartVideoRecord
*/
dvp2api dvpStatus dvpStopVideoRecord(dvpRecordHandle handle);


/**
*@brief ��ʾ�������ģ̬�Ի���
*@param[in] handle ������
*@param[in] hParent �����ڵĴ��ھ��
*/
dvp2api dvpStatus dvpShowPropertyModalDialog(dvpHandle handle, HWND hParent);


/**
*@brief ��ʾ���ѡ��Ի���
*@param[in] hParent �����ڵĴ��ھ��
*@param[out] pCameraInfo �����Ϣ
*/
dvp2api dvpStatus dvpShowSelectionDialog(HWND hParent, dvpCameraInfo *pCameraInfo);


/**
*@brief ������洢���ж�ȡ�û��Զ�������
*@param[in] handle ������
*@param[in] addr ��ȡ��ַ
*@param[in, out] pBuffer ͼ�����ݵ��ڴ��׵�ַ
*@param[in] size ���ݳ��ȣ�ͨ��������4k�ֽڣ�
*@see dvpWriteUserData
*@note ��ȡ�������ܴ��ڴ洢�������洢�ռ�
*@note ����@link #dvpOpen ��@endlink���������ʹ�ô˹���
*@warning �����ܼ���IO���������ܻ����Ľϳ��ĵȴ�ʱ��
*/
dvp2api dvpStatus dvpReadUserData(dvpHandle handle, dvpUint32 addr, void *pBuffer, dvpUint32 size);


/**
*@brief ���û��Զ�������д��������洢��
*@param[in] handle ������
*@param[in] addr д���ַ
*@param[in] pBuffer ͼ�����ݵ��ڴ��׵�ַ
*@param[in] size ���ݳ��ȣ�ͨ��������4k�ֽڣ�
*@see dvpReadUserData
*@note д���������ܴ��ڴ洢�������洢�ռ�
*@note ����@link #dvpOpen ��@endlink���������ʹ�ô˹���
*@warning �����ܼ���IO���������ܻ����Ľϳ��ĵȴ�ʱ��
*/
dvp2api dvpStatus dvpWriteUserData(dvpHandle handle, dvpUint32 addr, void *pBuffer, dvpUint32 size);


/**
*@brief Ϊ����趨һ��@link #dvpCameraInfo::UserID (User Defined Name) @endlink
*@param[in] handle ������
*@param[in] UserId �ַ���
*@param[in, out] pLength �����ṩ���ַ������ȣ����ʵ��ʹ�õ��ַ�������
*@see dvpGetCameraInfo
*/
dvp2api dvpStatus dvpSetUserId(dvpHandle handle, const char *UserId, dvpUint32 *pLength);


/** @} end of __DVP2_API_EXTEND__ */

/** @defgroup __DVP_EXPOSURE__ �ع⹦��
*@{
*/
/** @} end of __DVP_EXPOSURE__ */

/** @defgroup __DVP_COLOR__ ɫ�ʵ���
*@{
*/
/** @} end of __DVP_COLOR__ */

/** @defgroup __DVP_ENHANCE__ ��ǿЧ��
*@{
*/
/** @} end of __DVP_ENHANCE__ */

/** @defgroup __DVP_ADVANCED__ �߼�����
*@{
*/
/** @} end of __DVP_ADVANCED__ */

/** @defgroup __DVP_SIZE__ ͼ��ߴ�
*@{
*/
/** @} end of __DVP_SIZE__ */

/** @defgroup __DVP_TRIGGER__ ��������
*@{
*/
/** @} end of __DVP_TRIGGER__ */

/** @defgroup __DVP_INFORMATION__ ������Ϣ
*@{
*/
/** @} end of __DVP_INFORMATION__ */
/** @} end of __DVP2_API__ */

#endif /* __DVPCAMERA_H__ */



/****************************************************************************
 *  @doc INTERNAL BASEPIN
 *
 *  @module BasePin.h | Header file for the <c CTAPIBasePin> class methods
 *    used to implement the TAPI base output pin.
 ***************************************************************************/

#ifndef _BASEPIN_H_
#define _BASEPIN_H_

/*****************************************************************************
 * @doc EXTERNAL CONSTANTS
 *
 * @const 0x00000000 | CONVERSIONTYPE_NONE | No conversion operation necessary.
 *
 * @const 0x00000001 | CONVERSIONTYPE_ENCODE | Specifies an encoding operation.
 *
 * @const 0x00000002 | CONVERSIONTYPE_DECODE | Specifies a decoding operation.
 *
 * @const 0x00000004 | CONVERSIONTYPE_SCALER | Specifies an image size change.
 *
 * @const 0x00000008 | CONVERSIONTYPE_PRESCALER | Specifies an image size change will occur before a format change.
 ****************************************************************************/
#define CONVERSIONTYPE_NONE                                     0x00000000
#define CONVERSIONTYPE_ENCODE                           0x00000001
#define CONVERSIONTYPE_DECODE                           0x00000002
#define CONVERSIONTYPE_SCALER                           0x00000004
#define CONVERSIONTYPE_PRESCALER                        0x00000008

/****************************************************************************
 *  @doc INTERNAL CBASEPINCLASS
 *
 *  @class CTAPIBasePin | This class implements the TAPI base output pin.
 *
 *  @mdata CTAPIVCap* | CTAPIBasePin | m_pCaptureFilter | Pointer to the
 *    filter that owns us.
 *
 *  @mdata ALLOCATOR_PROPERTIES | CTAPIBasePin | m_parms | Out allocator
 *    properties.
 *
 *  @mdata REFERENCE_TIME | CTAPIBasePin | m_MaxProcessingTime | Maximum
 *    processing time.
 *
 *  @mdata REFERENCE_TIME | CTAPIBasePin | m_CurrentProcessingTime | Current
 *    processing time.
 *
 *  @mdata DWORD | CTAPIBasePin | m_dwMaxCPULoad | Maximum CPU load.
 *
 *  @mdata DWORD | CTAPIBasePin | m_dwCurrentCPULoad | Current CPU load.
 *
 *  @mdata REFERENCE_TIME | CTAPIBasePin | m_AvgTimePerFrameRangeMin | Minimum
 *    target frame rate.
 *
 *  @mdata REFERENCE_TIME | CTAPIBasePin | m_AvgTimePerFrameRangeMax | Maximum
 *    target frame rate.
 *
 *  @mdata REFERENCE_TIME | CTAPIBasePin | m_AvgTimePerFrameRangeSteppingDelta | Target
 *    frame rate stepping delta.
 *
 *  @mdata REFERENCE_TIME | CTAPIBasePin | m_AvgTimePerFrameRangeDefault | Target
 *    frame rate default.
 *
 *  @mdata REFERENCE_TIME | CTAPIBasePin | m_MaxAvgTimePerFrame | Target
 *    frame rate.
 *
 *  @mdata REFERENCE_TIME | CTAPIBasePin | m_CurrentAvgTimePerFrame | Current
 *    frame rate.
 *
 *  @mdata DWORD | CTAPIBasePin | m_dwBitrateRangeMin | Minimum target bitrate.
 *
 *  @mdata DWORD | CTAPIBasePin | m_dwBitrateRangeMax | Maximum target bitrate.
 *
 *  @mdata DWORD | CTAPIBasePin | m_dwBitrateRangeSteppingDelta | Target
 *    bitrate stepping delta.
 *
 *  @mdata DWORD | CTAPIBasePin | m_dwBitrateRangeDefault | Default target bitrate.
 *
 *  @mdata DWORD | CTAPIBasePin | m_dwMaxBitrate | Target bitrate.
 *
 *  @mdata DWORD | CTAPIBasePin | m_dwCurrentBitrate | Current bitrate.
 *
 *  @mdata BOOL | CTAPIBasePin | m_fFlipHorizontal | Set to TRUE if image is
 *    to be flipped horizontally.
 *
 *  @mdata BOOL | CTAPIBasePin | m_fFlipVertical | Set to TRUE if image is
 *    to be flipped vertically.
 *
 *  @mdata BOOL | CTAPIBasePin | m_fFlipVertical | Affects the quality of
 *    en encoded video stream.
 *
 *  @mdata DWORD  | CTAPIBasePin | m_dwConversionType | Specifies the format
 *    conversion operation necessary to go from the format of the captured
 *    video frames to the format of the data actually generated by the pin.
 *    It can be any combination of the following constants:
 *
 *  @flag CONVERSIONTYPE_NONE | No conversion operation necessary
 *  @flag CONVERSIONTYPE_ENCODE | Specifies an encoding operation
 *  @flag CONVERSIONTYPE_DECODE | Specifies a decoding operation
 *  @flag CONVERSIONTYPE_SCALER | Specifies an image size change
 *
 *  @mdata PBYTE | CTAPIBasePin | m_pbyOut | Pointer to the output buffer
 *    used in a conversion operation.
 *
 *  @mdata DWORD | CTAPIBasePin | m_dwLastTimestamp | Timestamps of the last
 *    frame generated, normalized to 29.97Hz.
 *
 *  @mdata DWORD | CTAPIBasePin | m_dwLastIFrameTime | Remembers the last
 *    time we sent an I-frame downstream.
 *
 *  @mdata DWORD | CTAPIBasePin | m_dwFrame | Current frame number.
 *
 *  @mdata HIC | CTAPIBasePin | m_hIC | Handle to the ICM image converter.
 *
 *  @mdata BOOL | CTAPIBasePin | m_fPeriodicIFrames | Set to TRUE to generate
 *    I-frame periodically.
 *
 *  @mdata PBITMAPINFOHEADER | CTAPIBasePin | m_pbiOut | Pointer to the output
 *    format.
 *
 *  @mdata PBITMAPINFOHEADER | CTAPIBasePin | m_pbiIn | Pointer to the input
 *    format.
 *
 *  @mdata PBITMAPINFOHEADER | CTAPIBasePin | m_pbiInt | Pointer to the intermediate
 *    format.
 *
 *  @mdata BOOL | CTAPIBasePin | m_fConvert | Set to TRUE after an ICM converter
 *    has been open successfully.
 *
 *  @mdata PBITMAPINFOHEADER | CTAPIBasePin | m_pbiSCCOut | Pointer to the output
 *    format of a software-only camera controlled operation.
 *
 *  @mdata PBITMAPINFOHEADER | CTAPIBasePin | m_pbiSCCIn | Pointer to the input
 *    format of a software-only camera controlled operation.
 *
 *  @mdata PBYTE | CTAPIBasePin | m_pbyCamCtrl | Intermediate buffer used in
 *    a software-only camera controlled operation.
 *
 *  @mdata BOOL | CTAPIBasePin | m_fSoftCamCtrl | Set to TRUE after a
 *    software-only camera controller has been opened.
 ***************************************************************************/
class CTAPIBasePin : public CBaseOutputPin, public CBaseStreamControl, public IAMStreamConfig, public IFrameRateControl, public IVideoControl, public IBitrateControl, public IMemAllocator
#ifdef USE_CPU_CONTROL
, public ICPUControl
#endif
{
        public:
        DECLARE_IUNKNOWN
        STDMETHODIMP NonDelegatingQueryInterface(IN REFIID riid, OUT PVOID *ppv);
        CTAPIBasePin(IN TCHAR *pObjectName, IN CTAPIVCap *pCaptureFilter, IN HRESULT *pHr, IN LPCWSTR pName);
        virtual ~CTAPIBasePin();

        // Override CBasePin base class methods
        virtual HRESULT GetMediaType(IN int iPosition, OUT CMediaType *pMediaType);
        virtual HRESULT CheckMediaType(IN const CMediaType *pMediaType);
        virtual HRESULT SetMediaType(IN CMediaType *pMediaType);

        // Implement IAMStreamConfig
        STDMETHODIMP SetFormat(IN AM_MEDIA_TYPE *pmt);
        STDMETHODIMP GetFormat(OUT AM_MEDIA_TYPE **ppmt);
        STDMETHODIMP GetNumberOfCapabilities(OUT int *piCount, OUT int *piSize);
        STDMETHODIMP GetStreamCaps(IN int iIndex, OUT AM_MEDIA_TYPE **ppmt, OUT LPBYTE pSCC);

#ifdef USE_CPU_CONTROL
        // Implement ICPUControl
        STDMETHODIMP SetMaxProcessingTime(IN REFERENCE_TIME MaxProcessingTime);
        STDMETHODIMP GetMaxProcessingTime(OUT REFERENCE_TIME *pMaxProcessingTime, IN DWORD dwMaxCPULoad);
        STDMETHODIMP GetCurrentProcessingTime(OUT REFERENCE_TIME *pCurrentProcessingTime);
        STDMETHODIMP GetMaxProcessingTimeRange(OUT REFERENCE_TIME *pMin, OUT REFERENCE_TIME *pMax, OUT REFERENCE_TIME *pSteppingDelta, OUT REFERENCE_TIME *pDefault, IN DWORD dwMaxCPULoad);
        STDMETHODIMP SetMaxCPULoad(IN DWORD dwMaxCPULoad);
        STDMETHODIMP GetMaxCPULoad(OUT DWORD *pdwMaxCPULoad, IN REFERENCE_TIME MaxProcessingTime);
        STDMETHODIMP GetCurrentCPULoad(OUT DWORD *pdwCurrentCPULoad);
        STDMETHODIMP GetMaxCPULoadRange(OUT DWORD *pMin, OUT DWORD *pMax, OUT DWORD *pSteppingDelta, OUT DWORD *pDefault, IN REFERENCE_TIME MaxProcessingTime);
#endif

        // Implement IFrameRateControl
        STDMETHODIMP GetRange(IN FrameRateControlProperty Property, OUT long *plMin, OUT long *plMax, OUT long *plSteppingDelta, OUT long *plDefault, OUT TAPIControlFlags *plCapsFlags);
        STDMETHODIMP Set(IN FrameRateControlProperty Property, IN long lValue, IN TAPIControlFlags lFlags);
        STDMETHODIMP Get(IN FrameRateControlProperty Property, OUT long *plValue, OUT TAPIControlFlags *plFlags);

        // Implement IBitrateControl
        STDMETHODIMP GetRange(IN BitrateControlProperty Property, OUT long *plMin, OUT long *plMax, OUT long *plSteppingDelta, OUT long *plDefault, OUT TAPIControlFlags *plCapsFlags, IN DWORD dwLayerId);
        STDMETHODIMP Set(IN BitrateControlProperty Property, IN long lValue, IN TAPIControlFlags lFlags, IN DWORD dwLayerId);
        STDMETHODIMP Get(IN BitrateControlProperty Property, OUT long *plValue, OUT TAPIControlFlags *plFlags, IN DWORD dwLayerId);

        // Implement IVideoControl
        STDMETHODIMP GetCaps(OUT LONG *pCapsFlags);
        STDMETHODIMP SetMode(IN LONG Mode);
        STDMETHODIMP GetMode(OUT LONG *Mode);
        STDMETHODIMP GetCurrentActualFrameRate(OUT LONGLONG *ActualFrameRate);
        STDMETHODIMP GetMaxAvailableFrameRate(IN LONG iIndex, IN SIZE Dimensions, OUT LONGLONG *MaxAvailableFrameRate);
        STDMETHODIMP GetFrameRateList(IN LONG iIndex, IN SIZE Dimensions, IN LONG *ListSize, OUT LONGLONG **FrameRates);

        // Implement IMemAllocator
        STDMETHODIMP SetProperties(IN ALLOCATOR_PROPERTIES *pRequest, OUT ALLOCATOR_PROPERTIES *pActual);
        STDMETHODIMP GetProperties(OUT ALLOCATOR_PROPERTIES *pProps);
        STDMETHODIMP Commit();
        STDMETHODIMP Decommit();
        STDMETHODIMP GetBuffer(OUT IMediaSample **ppBuffer, IN REFERENCE_TIME *pStartTime, IN REFERENCE_TIME *pEndTime, IN DWORD dwFlags);
        STDMETHODIMP ReleaseBuffer(IN IMediaSample *pBuffer);

        // Override CBaseOutputPin base class methods
        HRESULT DecideBufferSize(IN IMemAllocator *pAlloc, OUT ALLOCATOR_PROPERTIES *ppropInputRequest);
        HRESULT DecideAllocator(IN IMemInputPin *pPin, OUT IMemAllocator **ppAlloc);

        // Override IQualityControl interface method to receive Notification messages
        STDMETHODIMP Notify(IN IBaseFilter *pSelf, IN Quality q) {return E_NOTIMPL;};

        HRESULT Active();
        HRESULT Inactive();
        HRESULT ActiveRun(IN REFERENCE_TIME tStart);
        HRESULT ActivePause();
    HRESULT ChangeFormatHelper();
    HRESULT NotifyDeviceFormatChange(IN CMediaType *pMediaType);
        HRESULT Reconnect();

        protected:

        friend class CVfWCapDev;
        friend class CWDMCapDev;
        friend class CICMConverter;
        friend class CH26XEncoder;
        friend class CRtpPdPin;
        friend class CConverter;

        CTAPIVCap               *m_pCaptureFilter;

        // Allocator properties
        ALLOCATOR_PROPERTIES m_parms;

#ifdef USE_CPU_CONTROL
        // CPU control
        REFERENCE_TIME  m_MaxProcessingTime;
        REFERENCE_TIME  m_CurrentProcessingTime;
        DWORD                   m_dwMaxCPULoad;
        DWORD                   m_dwCurrentCPULoad;
#endif

        // Frame rate control
        LONG m_lAvgTimePerFrameRangeMin;
        LONG m_lAvgTimePerFrameRangeMax;
        LONG m_lAvgTimePerFrameRangeSteppingDelta;
        LONG m_lAvgTimePerFrameRangeDefault;
        LONG m_lMaxAvgTimePerFrame;
        LONG m_lCurrentAvgTimePerFrame;

        // Bitrate control
        LONG m_lBitrateRangeMin;
        LONG m_lBitrateRangeMax;
        LONG m_lBitrateRangeSteppingDelta;
        LONG m_lBitrateRangeDefault;
        LONG m_lTargetBitrate;
        LONG m_lCurrentBitrate;

        // Video mode control
        BOOL m_fFlipHorizontal;
        BOOL m_fFlipVertical;

        // Formats
        AM_MEDIA_TYPE*                                  *m_aFormats;
        DWORD                                                   m_dwNumFormats;
        const VIDEO_STREAM_CONFIG_CAPS* const *m_aCapabilities;
        int                                                             m_iCurrFormat;
        BOOL                                                    m_fFormatChanged;

        // Fast updates, this really only belongs to the capture pin, but it is
    // not worth while to override SendFrame just to read this flag.
        BOOL                            m_fFastUpdatePicture;

        // Format conversion
        CConverter *m_pConverter;
        HRESULT OpenConverter(IN PBITMAPINFOHEADER pbiIn, IN PBITMAPINFOHEADER pbiOut);
        HRESULT CloseConverter();

        // Blackbanding and cropping vs stretching
        BOOL m_fNoImageStretch;

        // ScaleDIB8 helpers
        DWORD m_dwBlackEntry;

#ifdef USE_SOFTWARE_CAMERA_CONTROL
        // Software-only camera control
        PBITMAPINFOHEADER m_pbiSCCOut;
        PBITMAPINFOHEADER m_pbiSCCIn;
        PBYTE m_pbyCamCtrl;
        BOOL m_fSoftCamCtrl;
        HRESULT CloseSoftCamCtrl();
        BOOL    IsSoftCamCtrlNeeded();
        BOOL    IsSoftCamCtrlOpen();
        HRESULT ApplySoftCamCtrl(PBYTE pbyInput, DWORD dwInBytes, PBYTE pbyOutput, PDWORD pdwBytesUsed, PDWORD pdwBytesExtent);
        HRESULT OpenSoftCamCtrl(IN PBITMAPINFOHEADER pbiIn, IN PBITMAPINFOHEADER pbiOut);
#endif

        // Video capture buffer queue management
    BOOL        Committed() {return m_pCaptureFilter->m_cs.paHdr != NULL;};
    HRESULT     Flush();
    HRESULT     ReleaseFrame(IN LPTHKVIDEOHDR ptvh);
    HRESULT     SendFrame(IN CFrameSample *pSample, IN PBYTE pbyInBuff, IN DWORD dwInBytes, OUT PDWORD pdwBytesUsed, OUT PDWORD pdwBytesExtent, IN BOOL bDiscon);
};

#endif // _BASEPIN_H_

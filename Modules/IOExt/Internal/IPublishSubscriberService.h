#include <usServiceInterface.h>
#include <string>
#include <functional>

#ifdef US_BUILD_SHARED_LIBS
#ifdef MitkIOExt_EXPORTS
#define PUBLISHSUBSCRIBERSERVICE_EXPORT US_ABI_EXPORT
#else
#define PUBLISHSUBSCRIBERSERVICE_EXPORT US_ABI_IMPORT
#endif
#else
#define PUBLISHSUBSCRIBERSERVICE_EXPORT US_ABI_EXPORT
#endif

struct PUBLISHSUBSCRIBERSERVICE_EXPORT IPublishSubscriberService
{
	// Out-of-line virtual desctructor for proper dynamic cast
	// support with older versions of gcc.
	virtual ~IPublishSubscriberService(){};
	virtual	void Register(const std::function<void(void)> method) = 0;
	virtual void Fire() = 0;
};
US_DECLARE_SERVICE_INTERFACE(IPublishSubscriberService, "org.mitk.PublishSubscrive")
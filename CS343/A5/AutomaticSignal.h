#ifndef AUTOMATICSIGNAL_H
#define AUTOMATICSIGNAL_H

#include <uC++.h>

#define AUTOMATIC_SIGNAL uCondition bench

#define WAITUNTIL(pred, before, after) \
	if (!pred) { \
		before; \
		while (!bench.empty()) { \
			bench.signal(); \
		} \
		while (!pred) { \
			bench.wait(); \
		} \
		after; \
	}

#define RETURN(expr...) \
	while (!bench.empty()) { \
		bench.signal(); \
	} \
	return (expr);

#endif


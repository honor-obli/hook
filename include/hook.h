/*
 * hook.h
 *
 *  Created on: 2015/10/12
 *      Author: honor
 */

#ifndef INCLUDE_HOOK_H_
#define INCLUDE_HOOK_H_


void* UglyHotpatch( void *target, const void *replacement );
void un_hook(void* target);


#endif /* INCLUDE_HOOK_H_ */

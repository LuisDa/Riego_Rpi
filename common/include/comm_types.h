/*
 * comm_types.h
 *
 *  Created on: 12/05/2012
 *      Author: luisda
 */

#ifndef COMM_TYPES_H_
#define COMM_TYPES_H_

#include "general_types.h"

//TODO A definir más a fondo.
typedef struct {
	byte estado_b0:1;
	byte estado_b1:1;
	byte estado_Rsv:6;
	word seq_number;
} estado_controlador_t;

#endif /* COMM_TYPES_H_ */

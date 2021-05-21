/* 
 * File:   app.h
 * Author: developer
 *
 * Created on July 22, 2015, 4:55 PM
 */

#ifndef APP_H
#define	APP_H

#ifdef	__cplusplus
extern "C" {
#endif

void AppInitialize(void);    
void AppProcess(void);
void AppTimer100us(void);
void AppINT_USART1_RX(char rxData);

#ifdef	__cplusplus
}
#endif

#endif	/* APP_H */


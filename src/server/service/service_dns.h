/*
 * dns.h
 */

#ifndef SERVER_SERVICE_DNS_H_
#define SERVER_SERVICE_DNS_H_

void service_dns_callback_connection_new(evutil_socket_t listener, short event, void *arg);

#endif /* SERVER_SERVICE_DNS_H_ */

#ifndef MIDDLEBOX_HTTPIN_HH
#define MIDDLEBOX_HTTPIN_HH
#include <click/element.hh>
#include "stackelement.hh"
#include "tcpelement.hh"

CLICK_DECLS

/*
=c

HTPPIn()

=s middlebox

entry point of an HTTP path in the stack of the middlebox

=d

This element is the entry point of an HTTP path in the stack of the middlebox by which all
HTTP packets must go before their HTTP content is processed. Each path containing an HTTPIn element
must also contain an HTTPOut element

=a HTTPOut */


class HTTPIn : public StackElement, public TCPElement
{
public:
    friend class HTTPOut;

    /** @brief Construct an HTTPIn element
     */
    HTTPIn() CLICK_COLD;

    const char *class_name() const        { return "HTTPIn"; }
    const char *port_count() const        { return PORTS_1_1; }
    const char *processing() const        { return PROCESSING_A_AH; }

    int configure(Vector<String> &, ErrorHandler *) CLICK_COLD;

protected:
    Packet* processPacket(struct fcb*, Packet*);

    virtual bool isLastUsefulPacket(struct fcb* fcb, Packet *packet);

private:
    /** @brief Remove an HTTP header from a request or a response
     * @param fcb Pointer to the FCB of the flow
     * @param packet Packet in which the header is located
     * @param header Name of the header to remove
     */
    void removeHeader(struct fcb *fcb, WritablePacket* packet, const char *header);

    /** @brief Return the content of an HTTP header
     * @param fcb Pointer to the FCB of the flow
     * @param packet Packet in which the header is located
     * @param headerName Name of the header to remove
     * @param buffer Buffer in which the content will be put
     * @param bufferSize Maximum size of the header (the content will be truncated if the buffer
     * is not large enough to contain it)
     */
    void getHeaderContent(struct fcb *fcb, WritablePacket* packet, const char* headerName,
        char* buffer, uint32_t bufferSize);

    /** @brief Process the headers and set the URL and the method in the httpin part of the FCB
     * @param fcb Pointer to the FCB of the flow
     * @param packet Packet in which the headers are located
     */
    void setRequestParameters(struct fcb *fcb, WritablePacket *packet);

    /** @brief Modify the HTTP version in the header to set it to 1.0
     * @param fcb Pointer to the FCB of the flow
     * @param packet Packet in which the headers are located
     * @return The packet with the HTTP version modified
     */
    WritablePacket* setHTTP10(struct fcb *fcb, WritablePacket *packet) CLICK_WARN_UNUSED_RESULT;
};

CLICK_ENDDECLS
#endif

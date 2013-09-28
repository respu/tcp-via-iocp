#pragma once

#include <WinSock2.h>
#include "socket.h"

//! Asynchronous Tcp server based on IO Completion ports
class Server
{
    //! Listening socket
    Socket _socket;

    //! Current connections
    std::size_t _connections_count;

    //! Completion port handle
    HANDLE _completion_port;

    //! AcceptEx function pointer
    LPFN_ACCEPTEX _acceptex_func;
    
    //! WSA init data
    WSADATA _wsa_data;

    //! WSA init flag
    bool _wsa_inited;

    //! OnWrite callback called when data was successfully transferred via socket
    typedef std::function<void(const Connection*, std::size_t)> OnWriteCallback;
    OnWriteCallback OnWrite;

    //! OnRead callback called when data was successfully read from socket
    typedef std::function<void(const Connection*, void*, std::size_t)> OnReadCallback;
    OnReadCallback OnRead;

    //! OnClientConnected callback called when new client connected to listening socket
    typedef std::function<void(const Connection*)> OnClientConnectedCallback;
    OnClientConnectedCallback OnClientConnected;

    //! OnClientDisconnected callback called when client closed connection
    typedef std::function<void(const Connection*)> OnClientDisconnectedCallback;
    OnClientDisconnectedCallback OnClientDisconnected;

public:
    Server();
    ~Server();

    //! Initialization. Must be called before any other method
    void Init(const std::string& address, unsigned port);

    //! Start async wait for new connections
    void StartAccept();

    //! Start async write operation
    void WriteAsync(const Connection* conn, void* data, std::size_t size);

    //! Start async read operation
    void ReadAsync(const Connection* conn);

    //! Run the server
    void Run();

    //! Check server was initialized
    void CheckInited() const;

public:
    void SetOnWriteCallback(OnWriteCallback callback);
    void SetOnReadCallback(OnReadCallback callback);
    void SetOnClientConnectedCallback(OnClientConnectedCallback callback);
    void SetOnClientDisconnectedCallback(OnClientDisconnectedCallback callback);
};
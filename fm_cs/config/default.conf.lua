#!/usr/local/bin/luajit

services =
{
    {
      name = "gateway",
      id   = 1,
    },
    {
      name = "rpc",
      id   = 2,
    },
}

network =
{
  io_context =
  {
    [1] =
    {
      name      = "default",
      id        = 1,
      interface =
      {
        [1] =
        {
          name                 = "connection_server",
          type                 = "server",
          protocal             = "tcp",
          ip4                  = "0.0.0.0",
          ip6                  = "",
          port                 = 20000,
          max_connection       = 65535,
          package_max_length   = 32768,
          package_max          = 64,
          backlog              = 300,
          enable_nodelay       = true,
          enable_oob           = false,
          gateway              = "gateway",
        },
        [2] =
        {
          name                 = "rpc_client",
          type                 = "client",
          protocal             = "tcp",
          ip4                  = "127.0.0.1",
          ip6                  = "",
          port                 = 10000,
          package_max_length   = 32768,
          package_max          = 64,
          enable_nodelay       = true,
          enable_oob           = false,
          gateway              = "rpc",
          reconnect_timeout    = 3000,
        },
      },
    },
  },
}

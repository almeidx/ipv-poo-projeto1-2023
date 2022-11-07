#ifndef USERPERMISSIONS_H
#define USERPERMISSIONS_H

enum UserPermissions {
     ADICIONAR = 1 << 0,
     REMOVER = 1 << 1,
     LISTAR = 1 << 2,
     RUN = 1 << 3,
     MANUTENCAO = 1 << 4
};

#endif // USERPERMISSIONS_H

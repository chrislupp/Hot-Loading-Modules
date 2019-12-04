/*
    Hot Loading Modules Tutorial

    This source file was adapted from:

    https://github.com/knusbaum/CPP-Dynamic-Class-Loading
*/
#pragma once

#include <memory>
#include <string>
#include <iostream>

#include <dlfcn.h>

using std::shared_ptr;


/*
    \brief Dynamic module loader
*/
template <class Type>
class Module
{
public:
    // \brief Default constructor
    Module() { ptr_ = std::make_shared<SharedObject>(); };

    // \brief Destructor
    ~Module() {};

    /*!
        \brief Dynamically loads a user-defined module
    */
    void SetModuleName(std::string name)
    {
        name_ = name;
    }

    /*
        \brief Creates the object
    */
    shared_ptr<Type> CreateObject()
    {
        if(!ptr_->create || !ptr_->destroy)
            if(!ptr_->LoadModule(name_))
                return shared_ptr<Type>(NULL);

        // create a local variable of the shared object pointer
        shared_ptr<SharedObject> ptr = ptr_;

        // destructor function
        auto destructor = [ptr](Type *obj) { ptr->destroy(obj); };

        return shared_ptr<Type>(ptr_->create(), destructor);
    };
    
private:
    struct SharedObject
    {
        typename Type::Create *create = NULL;
        typename Type::Destroy *destroy = NULL;
        void *dll_handle = NULL;

        ~SharedObject()
        {
            CloseModule();
        };

        /*!
            \brief Loads a module
        */
        bool LoadModule(std::string module)
        {
            dll_handle = dlopen(module.c_str(), RTLD_LAZY);

            if(!dll_handle)
            {
                std::cerr << "Failed to open library: " << dlerror()
                    << std::endl;
                return false;
            }

            // Reset errors
            dlerror();

            create = (typename Type::Create*) dlsym(dll_handle, "Create");
            const char * err = dlerror();
            if(err)
            {
                std::cerr << "Failed to load create symbol: " << err
                    << std::endl;
                CloseModule();
                return false;
            }
            
            destroy = (typename Type::Destroy*) dlsym(dll_handle, "Destroy");
            err = dlerror();
            if(err) {
                std::cerr << "Failed to load destroy symbol: " << err
                    << std::endl;
                CloseModule();
                return false;
            }

            return true;
        };

        /*!
            \brief Closes the module
        */
        void CloseModule()
        {
            if(dll_handle)
            {
                dlclose(dll_handle);
                dll_handle = NULL;
            }
            if(create)
                create = NULL;
            if(destroy)
                destroy = NULL;
        };
    };

    // \brief Name of the module
    std::string name_;

    // \brief Pointer to the created object
    shared_ptr<SharedObject> ptr_;
};
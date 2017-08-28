/*
 *  Copyright (c) Hubert Jarosz. All rights reserved.
 *  Licensed under the MIT license. See LICENSE file in the project root for full license information.
 */

#include <dynamicLinker.hpp>
#include <WinBase.h>

namespace dynamicLinker {

  bool dynamicLinker::closeLib() {
#ifdef _WIN32
  return FreeLibrary( (HINSTANCE) lib->ptr() );
#else
  return ( dlclose( lib->ptr() ) == 0 );
#endif
  }

  void * dynamicLinker::openLib() {
#ifdef _WIN32
  return LoadLibrary( libPath.c_str() );
#else
  return dlopen( libPath.c_str(), RTLD_NOW | RTLD_LOCAL );
#endif
  }

  dynamicLinker::dynamicLinker( std::string path ) : libPath(path) {
  }

  std::shared_ptr<dynamicLinker> dynamicLinker::make_new( std::string path ) {
    auto x = new dynamicLinker(path);
    return std::shared_ptr<dynamicLinker>(x);
  }

  bool dynamicLinker::open() {
    // C++14:
    // lib = std::make_unique<_void>( dlopen( libPath.c_str(), RTLD_NOW | RTLD_LOCAL ) );
    auto v = new _void( openLib() );
    lib = std::unique_ptr<_void>( v );

    if ( lib->ptr() == nullptr ) {
      lib = nullptr;
      char* err = nullptr;
      std::string s = (err == nullptr) ? "FATAL ERROR: no error!" : std::string(err);
      throw openException(s);
    }

    return true;
  }

  dynamicLinker::~dynamicLinker() {
    if( lib != nullptr ) {
      if( ! closeLib() ) {
        lib.reset();
        return;
      }
      lib->null();
      lib = nullptr;
    }
  }

  dynamicLinker::_void::_void( void * ptr ) : myself(ptr) {}

  dynamicLinker::_void::~_void() {
    if( myself != nullptr ) {
      std::free(myself);
      myself = nullptr;
    }
  }

  void * dynamicLinker::_void::ptr() const {
    return myself;
  }

  void dynamicLinker::_void::null() {
    myself = nullptr;
  }

}; // namespace dynamicLinker

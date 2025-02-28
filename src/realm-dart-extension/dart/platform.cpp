////////////////////////////////////////////////////////////////////////////////
//
// Copyright 2021 Realm Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
////////////////////////////////////////////////////////////////////////////////

#include <stdexcept>
#include <vector>
#include <stdarg.h>
#include <stdio.h>
#ifdef _WIN32
#include <direct.h>
#else
#include <unistd.h>
#endif
//#include <uv.h>


#ifdef FLUTTER
#include "dart_types.hpp"
#endif

#include "../realm-js-common/platform.hpp"

namespace realm {

//class UVException : public std::runtime_error {
//public:
//    UVException(uv_errno_t error)
//    : std::runtime_error(uv_strerror(error))
//    , m_error(error)
//    { }
//
//    const uv_errno_t m_error;
//};
//
//struct FileSystemRequest : uv_fs_t {
//    ~FileSystemRequest() {
//        uv_fs_req_cleanup(this);
//    }
//};

// taken from Node.js: function Cwd in node.cc
std::string default_realm_file_directory()
{
    //throw std::runtime_error("not implemented");

#ifdef _WIN32
  /* MAX_PATH is in characters, not bytes. Make sure we have enough headroom. */
  //char buf[_MAX_PATH * 4];
  char* cwd = _getcwd(0, 0);
  return std::string(cwd);
#elif FLUTTER
    if (realm::dartvm::flutter::FilesDir == "") {
        throw std::runtime_error("FilesDir not set");
    }

    return realm::dartvm::flutter::FilesDir;
#else
  char* cwd = getcwd(0, 0);
  return std::string(cwd);
#endif
    
   /* size_t cwd_len = sizeof(buf);
    int err = uv_cwd(buf, &cwd_len);
    if (err) {
        throw UVException(static_cast<uv_errno_t>(err));
    }*/
    //return std::string(buf, cwd_len);
}

void ensure_directory_exists_for_file(const std::string &file_path)
{
    //size_t pos = 0;

    //while ((pos = file_path.find_first_of('/', pos)) != std::string::npos) {
    //    // Skip for leading slash.
    //    if (pos == 0) {
    //        pos++;
    //        continue;
    //    }

    //    std::string dir_path = file_path.substr(0, pos++);
    //    FileSystemRequest req;
    //    if (uv_fs_mkdir(uv_default_loop(), &req, dir_path.c_str(), 0755, nullptr) < 0 && req.result != UV_EEXIST) {
    //        throw UVException(static_cast<uv_errno_t>(req.result));
    //    }
    //}
}

void copy_bundled_realm_files()
{
    throw std::runtime_error("Realm for Node does not support this method.");
}

inline bool ends_with(const std::string& str, const std::string& suffix) {
    return str.size() > suffix.size() && str.compare(str.size() - suffix.size(), suffix.size(), suffix) == 0;
}

void remove_realm_files_from_directory(const std::string &dir_path)
{
    /*FileSystemRequest scandir_req;
    if (uv_fs_scandir(uv_default_loop(), &scandir_req, dir_path.c_str(), 0, nullptr) < 0) {
        throw UVException(static_cast<uv_errno_t>(scandir_req.result));
    }

    uv_dirent_t entry;
    while (uv_fs_scandir_next(&scandir_req, &entry) != UV_EOF) {
        std::string path(dir_path + '/' + entry.name);

        if (entry.type == UV_DIRENT_DIR) {
            static std::string realm_management_extension(".realm.management");
            if (ends_with(path, realm_management_extension)) {
                uv_dirent_t management_entry;
                FileSystemRequest management_scandir_req;
                if (uv_fs_scandir(uv_default_loop(), &management_scandir_req, path.c_str(), 0, nullptr) < 0) {
                    throw UVException(static_cast<uv_errno_t>(scandir_req.result));
                }

                while (uv_fs_scandir_next(&management_scandir_req, &management_entry) != UV_EOF) {
                    std::string management_entry_path = path + '/' + management_entry.name;
                    FileSystemRequest delete_req;
                    if (uv_fs_unlink(uv_default_loop(), &delete_req, management_entry_path.c_str(), nullptr) != 0) {
                        throw UVException(static_cast<uv_errno_t>(delete_req.result));
                    }
                }

                FileSystemRequest management_rmdir_req;
                if (uv_fs_rmdir(uv_default_loop(), &management_rmdir_req, path.c_str(), nullptr)) {
                    throw UVException(static_cast<uv_errno_t>(management_rmdir_req.result));
                }
            }
        } else {
            static std::string realm_extension(".realm");
            static std::string realm_note_extension(".realm.note");
            static std::string realm_lock_extension(".realm.lock");
            if (ends_with(path, realm_extension) || ends_with(path, realm_note_extension) || ends_with(path, realm_lock_extension)) {
                FileSystemRequest delete_req;
                if (uv_fs_unlink(uv_default_loop(), &delete_req, path.c_str(), nullptr) != 0) {
                    throw UVException(static_cast<uv_errno_t>(delete_req.result));
                }
            }
        }
    }*/
}

void remove_directory(const std::string &path)
{
    //FileSystemRequest exists_req;
    //if (uv_fs_stat(uv_default_loop(), &exists_req, path.c_str(), nullptr) != 0) {
    //    if (exists_req.result == UV_ENOENT) {
    //        // path doesn't exist, ignore
    //        return;
    //    } else {
    //        throw UVException(static_cast<uv_errno_t>(exists_req.result));
    //    }
    //}

    //uv_dirent_t dir_entry;
    //FileSystemRequest dir_scan_req;
    //if (uv_fs_scandir(uv_default_loop(), &dir_scan_req, path.c_str(), 0, nullptr) < 0) {
    //    throw UVException(static_cast<uv_errno_t>(dir_scan_req.result));
    //}

    //while (uv_fs_scandir_next(&dir_scan_req, &dir_entry) != UV_EOF) {
    //    std::string dir_entry_path = path + '/' + dir_entry.name;
    //    FileSystemRequest delete_req;
    //    if (uv_fs_unlink(uv_default_loop(), &delete_req, dir_entry_path.c_str(), nullptr) != 0) {
    //        throw UVException(static_cast<uv_errno_t>(delete_req.result));
    //    }
    //}

    //FileSystemRequest rmdir_req;
    //if (uv_fs_rmdir(uv_default_loop(), &rmdir_req, path.c_str(), nullptr)) {
    //    throw UVException(static_cast<uv_errno_t>(rmdir_req.result));
    //}
}


void remove_file(const std::string &path)
{
    /*std::string extension = path.substr(path.find_last_of(".") + 1);
    if (extension != "realm") {
        throw std::runtime_error("not implemented for this file extension");
    }*/

#ifdef _WIN32
    /* MAX_PATH is in characters, not bytes. Make sure we have enough headroom. */
    //char buf[_MAX_PATH * 4];
    //std::remove(path.c_str());
#else
    throw std::runtime_error("not implemented for this platform");
#endif


















    //FileSystemRequest exists_req;
    //if (uv_fs_stat(uv_default_loop(), &exists_req, path.c_str(), nullptr) != 0) {
    //    if (exists_req.result == UV_ENOENT) {
    //        // path doesn't exist, ignore
    //        return;
    //    } else {
    //        throw UVException(static_cast<uv_errno_t>(exists_req.result));
    //    }
    //}

    //FileSystemRequest delete_req;
    //if (uv_fs_unlink(uv_default_loop(), &delete_req, path.c_str(), nullptr) != 0) {
    //    throw UVException(static_cast<uv_errno_t>(delete_req.result));
    //}
}


} // realm

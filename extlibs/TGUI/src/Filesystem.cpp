/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TGUI - Texus' Graphical User Interface
// Copyright (C) 2012-2021 Bruno Van de Velde (vdv_b@tgui.eu)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#include <TGUI/Filesystem.hpp>

#include <cstdlib> // getenv

#if !defined(TGUI_SYSTEM_WINDOWS)
    #include <unistd.h> // getuid
    #include <pwd.h> // getpwuid
#endif

#if !defined(TGUI_USE_STD_FILESYSTEM) && !defined(TGUI_SYSTEM_WINDOWS)
    #include <errno.h> // errno
    #include <unistd.h> // getcwd
#endif

#if !defined(TGUI_USE_STD_FILESYSTEM_FILE_TIME)
    #if defined(TGUI_SYSTEM_WINDOWS)
        #include <TGUI/WindowsInclude.hpp>
    #else
        #include <sys/types.h> // stat
        #include <sys/stat.h> // stat
        #include <unistd.h> // getcwd
        #include <dirent.h> // opendir, readdir, closedir
    #endif
#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace tgui
{
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#if defined(TGUI_SYSTEM_WINDOWS)
    static std::time_t FileTimeToUnixTime(FILETIME const& FileTime)
    {
        const auto WINDOWS_TICK = 10000000ULL;
        const auto SEC_TO_UNIX_EPOCH = 11644473600LL;

        ULARGE_INTEGER DateTime;
        DateTime.LowPart = FileTime.dwLowDateTime;
        DateTime.HighPart = FileTime.dwHighDateTime;
        return static_cast<std::time_t>(DateTime.QuadPart / 10000000ULL - 11644473600ULL);
    }
#endif

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Filesystem::Path::Path(const String& path)
#ifdef TGUI_USE_STD_FILESYSTEM
        : m_path(std::u32string(path))
#endif
    {
#if !defined(TGUI_USE_STD_FILESYSTEM)
        String part;
        for (const char32_t c : path)
        {
    #if defined(TGUI_SYSTEM_WINDOWS)
            if ((c == '/') || (c == '\\'))
    #else
            if (c == '/')
    #endif
            {
                // If this is the first part then check if we are parsing an absolute path
                if (m_parts.empty() && !m_absolute && m_root.empty())
                {
    #if defined(TGUI_SYSTEM_WINDOWS)
                    if (part.empty() || ((part.length() == 2) && (part[1] == U':')))
                    {
                        m_root = part;
                        m_absolute = true;
                    }
    #else
                    if (part.empty())
                        m_absolute = true;
    #endif
                    else // The path is relative, there is no root part
                        m_parts.push_back(part);
                }
                else // There have already been other parts, so just add this one
                {
                    if (!part.empty())
                        m_parts.push_back(part);
                }

                part.clear();
            }
            else
                part.push_back(c);
        }

        if (!part.empty())
        {
    #if defined(TGUI_SYSTEM_WINDOWS)
            if (!m_absolute && m_root.empty() && (part.length() == 2) && (part[1] == U':'))
            {
                m_root = part;
                m_absolute = true;
            }
            else
                m_parts.push_back(part);
    #else
            m_parts.push_back(part);
    #endif
        }
        else // The was no filename
        {
            // If the last character was a slash then add an empty filename
            if (!path.empty())
                m_parts.push_back("");
        }
#endif
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    bool Filesystem::Path::isEmpty() const
    {
#ifdef TGUI_USE_STD_FILESYSTEM
        return m_path.empty();
#else
        return !m_absolute && m_root.empty() && m_parts.empty();
#endif
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    String Filesystem::Path::asString() const
    {
#ifdef TGUI_USE_STD_FILESYSTEM
        return m_path.generic_u32string();
#else
        String str = m_root;
        if (m_absolute)
            str += U'/';

        if (!m_parts.empty())
            str += m_parts[0];

        for (unsigned int i = 1; i < m_parts.size(); ++i)
            str += U'/' + m_parts[i];

        return str;
#endif
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Filesystem::Path Filesystem::Path::getParentPath() const
    {
#ifdef TGUI_USE_STD_FILESYSTEM
        Path parentPath;
        parentPath.m_path = m_path.parent_path();
#else
        Path parentPath(*this);
        if (!parentPath.m_parts.empty())
            parentPath.m_parts.pop_back();
#endif
        return parentPath;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    String Filesystem::Path::getFilename() const
    {
#ifdef TGUI_USE_STD_FILESYSTEM
        return m_path.filename().generic_u32string();
#else
        if (!m_parts.empty())
            return m_parts.back();
        else
            return "";
#endif
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Filesystem::Path Filesystem::Path::getNormalForm() const
    {
#ifdef TGUI_USE_STD_FILESYSTEM
        return Path(m_path.lexically_normal());
#else
        Filesystem::Path newPath = *this;
        for (std::size_t i = newPath.m_parts.size(); i > 0; --i)
        {
            if (newPath.m_parts[i-1] == U".")
                newPath.m_parts.erase(newPath.m_parts.begin() + (i-1));
            else if (m_parts[i-1] == U"..")
            {
                if (i > 1)
                {
                    newPath.m_parts.erase(newPath.m_parts.begin() + (i-2), newPath.m_parts.begin() + i);
                    --i;
                }
                else
                    newPath.m_parts.clear();
            }
        }

        return newPath;
#endif
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifdef TGUI_SYSTEM_WINDOWS
    std::wstring Filesystem::Path::asNativeString() const
    {
    #ifdef TGUI_USE_STD_FILESYSTEM
        return m_path.wstring();
    #else
        String str = m_root;
        if (m_absolute)
            str += U'\\';

        if (!m_parts.empty())
            str += m_parts[0];

        for (unsigned int i = 1; i < m_parts.size(); ++i)
            str += U'\\' + m_parts[i];

        return std::wstring(str);

    #endif
    }
#else
    std::string Filesystem::Path::asNativeString() const
    {
    #ifdef TGUI_USE_STD_FILESYSTEM
        return m_path.generic_string();
    #else
        return std::string(asString());
    #endif
    }
#endif

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Filesystem::Path Filesystem::Path::operator/(const Path& path) const
    {
        return Path(*this) /= path;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Filesystem::Path& Filesystem::Path::operator/=(const Path& path)
    {
#ifdef TGUI_USE_STD_FILESYSTEM
        m_path /= path.m_path;
#else
        if (!path.m_absolute)
        {
            // If the path contained a directory then it might have an empty filename at the end. Remove it first.
            if (!m_parts.empty() && m_parts.back().empty())
                m_parts.pop_back();

            m_parts.insert(m_parts.end(), path.m_parts.begin(), path.m_parts.end());
        }
        else // The path to append is absolute, so just replace the current path
            *this = path;
#endif
        return *this;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    bool Filesystem::Path::operator==(const Path& other) const
    {
#ifdef TGUI_USE_STD_FILESYSTEM
        return m_path == other.m_path;
#else
        return (m_parts == other.m_parts) && (m_root == other.m_root) && (m_absolute == other.m_absolute);
#endif
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    bool Filesystem::Path::operator!=(const Path& other) const
    {
        return !(*this == other);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    bool Filesystem::directoryExists(const Path& path)
    {
#ifdef TGUI_USE_STD_FILESYSTEM
        std::error_code errorCode;
        return std::filesystem::is_directory(path, errorCode);
#elif defined(TGUI_SYSTEM_WINDOWS)
        const DWORD attrib = GetFileAttributesW(path.asNativeString().c_str());
        return ((attrib != INVALID_FILE_ATTRIBUTES) && (attrib & FILE_ATTRIBUTE_DIRECTORY));
#else
        struct stat fileInfo;
        return (stat(path.asNativeString().c_str(), &fileInfo) == 0) && (fileInfo.st_mode & S_IFDIR);
#endif
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    bool Filesystem::fileExists(const Path& path)
    {
#ifdef TGUI_USE_STD_FILESYSTEM
        std::error_code errorCode;
        return std::filesystem::exists(path, errorCode);
#elif defined(TGUI_SYSTEM_WINDOWS)
        const DWORD attrib = GetFileAttributesW(path.asNativeString().c_str());
        return attrib != INVALID_FILE_ATTRIBUTES;
#else
        struct stat fileInfo;
        return stat(path.asNativeString().c_str(), &fileInfo) == 0;
#endif
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    bool Filesystem::createDirectory(const Path& path)
    {
#ifdef TGUI_USE_STD_FILESYSTEM
        std::error_code errorCode;
        return std::filesystem::create_directory(path, errorCode);
#elif defined(TGUI_SYSTEM_WINDOWS)
        const DWORD status = CreateDirectoryW(path.asNativeString().c_str(), NULL);
        return (status != 0) || (GetLastError() == ERROR_ALREADY_EXISTS);
#else
        const int status = mkdir(path.asNativeString().c_str(), S_IRWXU | S_IRWXG | S_IRWXO);
        return (status == 0) || (errno == EEXIST);
#endif
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Filesystem::Path Filesystem::getHomeDirectory()
    {
#ifdef TGUI_SYSTEM_WINDOWS
    #if defined (_MSC_VER)
        const DWORD requiredBufferSizeHomeDrive = GetEnvironmentVariableW(L"HOMEDRIVE", nullptr, 0);
        auto bufferHomeDrive = std::make_unique<wchar_t[]>(requiredBufferSizeHomeDrive);
        const DWORD lengthHomeDrive = GetEnvironmentVariableW(L"HOMEDRIVE", bufferHomeDrive.get(), requiredBufferSizeHomeDrive);

        const DWORD requiredBufferSizeHomePath = GetEnvironmentVariableW(L"HOMEPATH", nullptr, 0);
        auto bufferHomePath = std::make_unique<wchar_t[]>(requiredBufferSizeHomePath);
        const DWORD lengthHomePath = GetEnvironmentVariableW(L"HOMEPATH", bufferHomePath.get(), requiredBufferSizeHomePath);

        if ((lengthHomeDrive + 1 == requiredBufferSizeHomeDrive) && (lengthHomePath + 1 == requiredBufferSizeHomePath))
            return Path(String(bufferHomeDrive.get(), lengthHomeDrive) + String(bufferHomePath.get(), lengthHomePath));
    #else
        const char* homeDrive = std::getenv("HOMEDRIVE");
        const char* homePath = std::getenv("HOMEPATH");
        if (homeDrive && homePath)
            return Path(homeDrive) / Path(homePath);
    #endif
#else
        const char* homeDir = std::getenv("HOME");
        if (!homeDir)
            homeDir = getpwuid(getuid())->pw_dir;

        if (homeDir)
            return Path(homeDir);
#endif

        return Path();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Filesystem::Path Filesystem::getCurrentWorkingDirectory()
    {
#ifdef TGUI_USE_STD_FILESYSTEM
        std::error_code errorCode;
        return Path{std::filesystem::current_path(errorCode)};
#elif defined(TGUI_SYSTEM_WINDOWS)
        const DWORD requiredBufferSize = GetCurrentDirectoryW(0, nullptr);
        auto buffer = std::make_unique<wchar_t[]>(requiredBufferSize);
        const DWORD pathLength = GetCurrentDirectoryW(requiredBufferSize, buffer.get());
        if (pathLength + 1 == requiredBufferSize)
            return Path(String(buffer.get(), pathLength));
#else
        const unsigned BUFFER_SIZE = 4096; // More than enough for any reasonable use and doesn't rely on PATH_MAX
        char buffer[BUFFER_SIZE];
        if (getcwd(buffer, BUFFER_SIZE))
            return Path(buffer);
#endif

        return Path();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Filesystem::Path Filesystem::getLocalDataDirectory()
    {
        Path localDataDir;
#ifdef TGUI_SYSTEM_WINDOWS
    #if defined (_MSC_VER)
        const DWORD requiredBufferSize = GetEnvironmentVariableW(L"LOCALAPPDATA", nullptr, 0);
        auto buffer = std::make_unique<wchar_t[]>(requiredBufferSize);
        const DWORD length = GetEnvironmentVariableW(L"LOCALAPPDATA", buffer.get(), requiredBufferSize);
        if (length + 1 == requiredBufferSize)
            localDataDir = Path(String(buffer.get(), length));
    #else
        const char* appDataDir = std::getenv("LOCALAPPDATA");
        if (appDataDir)
            localDataDir = Path(appDataDir);
    #endif
#else
        const char* homeDir = std::getenv("HOME");
        if (!homeDir)
            homeDir = getpwuid(getuid())->pw_dir;
        if (homeDir)
        {
    #ifdef TGUI_SYSTEM_MACOS
            localDataDir = Path(homeDir) / U"Library" / U"Application Support";
    #else
            localDataDir = Path(homeDir) / U".local" / U"share";
    #endif
        }
#endif

        return localDataDir;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    std::vector<Filesystem::FileInfo> Filesystem::listFilesInDirectory(const Path& path)
    {
        std::vector<FileInfo> fileList;

#ifdef TGUI_USE_STD_FILESYSTEM_FILE_TIME
        std::error_code errorCode;
        for (const auto& entry: std::filesystem::directory_iterator(path, std::filesystem::directory_options::skip_permission_denied, errorCode))
        {
            TGUI_EMPLACE_BACK(fileInfo, fileList)
            fileInfo.filename = entry.path().filename().generic_u32string();
            fileInfo.path = Path(entry.path());
            fileInfo.directory = entry.is_directory(errorCode);
            fileInfo.modificationTime = std::chrono::system_clock::to_time_t(std::chrono::clock_cast<std::chrono::system_clock>(entry.last_write_time(errorCode)));
            if (!fileInfo.directory)
                fileInfo.fileSize = entry.file_size(errorCode);
        }
#elif defined(TGUI_SYSTEM_WINDOWS)
        WIN32_FIND_DATAW entry;
        HANDLE FileHandle = FindFirstFileW((path.asNativeString() + L"\\*").c_str(), &entry);
        if (FileHandle == INVALID_HANDLE_VALUE)
            return fileList;

        do
        {
            String filename = entry.cFileName;
            if ((filename == U".") || (filename == U".."))
                continue;

            TGUI_EMPLACE_BACK(fileInfo, fileList)
            fileInfo.filename = filename;
            fileInfo.path = path / filename;
            fileInfo.directory = (entry.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0;

            fileInfo.modificationTime = FileTimeToUnixTime(entry.ftLastWriteTime);
            if (!fileInfo.directory)
                fileInfo.fileSize = (entry.nFileSizeHigh * (static_cast<decltype(fileInfo.fileSize)>(MAXDWORD) + 1)) + entry.nFileSizeLow;

        } while (FindNextFileW(FileHandle, &entry) != 0);

        FindClose(FileHandle);
#else
        DIR* dir = opendir(path.asNativeString().c_str());
        if (!dir)
            return fileList;

        struct dirent* entry = nullptr;
        while ((entry = readdir(dir)) != NULL)
        {
            const String filename(entry->d_name);
            if ((filename == ".") || (filename == ".."))
                continue;

            const Path filePath = path / filename;

            struct stat statFileInfo;
            if (stat(filePath.asNativeString().c_str(), &statFileInfo) != 0)
                continue;

            if (statFileInfo.st_size < 0)
                continue;

            TGUI_EMPLACE_BACK(fileInfo, fileList)
            fileInfo.filename = filename;
            fileInfo.path = filePath;
            fileInfo.directory = (statFileInfo.st_mode & S_IFDIR);
            fileInfo.modificationTime = statFileInfo.st_mtime;
            if (!fileInfo.directory)
                fileInfo.fileSize = static_cast<decltype(fileInfo.fileSize)>(statFileInfo.st_size);
        }

        closedir(dir);
#endif

        return fileList;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

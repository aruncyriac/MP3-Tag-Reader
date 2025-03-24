# MP3-Tag-Reader

## Overview
MP3-Tag-Reader is a command-line tool for reading and editing ID3v2.3 tags in MP3 files. It parses common metadata fields such as title, artist, album, year, genre, and comments, allowing users to view and modify them.

## Features
- **Read MP3 Metadata**: Extracts ID3v2.3 tags, displaying song details.
- **Edit Tags**: Modifies specific metadata fields while preserving the MP3 structure.
- **Efficient Parsing**: Reads frame headers and updates only the required data.
- **Temporary File Handling**: Uses a temp file to ensure data integrity before writing changes back.

## How It Works
- **ID3v2.3 Structure**: 
  - The first 10 bytes contain metadata and tag size.
  - Each frame includes a 10-byte header with an ID, size, and flags, followed by content.
- **Editing Process**:
  - The program locates a frame, modifies its content, and updates the file without corruption.

## Usage
### View MP3 file metadata:
```
./a.out -v <file>
```
### Edit MP3 file metadata:
**Tags:**
- `-t` → Edit song title
- `-a` → Edit artist name
- `-A` → Edit album name
- `-y` → Edit year
- `-M` → Edit genre
- `-c` → Edit comment

**Example:**
```
./a.out -w <file> <tag>
```

## Notes
- The tool ensures minimal data loss by carefully modifying only the necessary tag fields.
- It uses temporary files to apply changes safely.


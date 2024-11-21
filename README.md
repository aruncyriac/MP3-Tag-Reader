# MP3-Tag-Reader
To create an MP3 ID3v2.3 tag reader and editor, you need to handle the tag's structure, parse the first six common
frames (TIT2 for title, TPE1 for artist, TALB for album, TYER for year, TCON for content, and COMM for comment), 
and allow modification. ID3v2.3 starts with a 10-byte header containing metadata and the tag's total size. Each 
frame has a 10-byte header (frame ID, size, and flags), followed by its content. The program reads the header, 
parses frame data, and displays it. For editing, it locates the relevant frame, modifies its content while
maintaining the structure, and writes back changes.Here we use a temp file and rewrite it back to orginal file

To view mp3 file contents<br>
INFO:./a.out -v &ltfile&gt  <br>
To edit mp3 file contents <br>
'<Tags>' <br>
 -t -> to edit song title<br>
 -a -> to edit artist name<br>
 -A -> to edit album name<br>
 -y -> to edit year<br>
 -M -> to edit content<br>
 -c -> to edit comment<br>
INFO:./a.out -w '<file>' '<tag>'  <br>

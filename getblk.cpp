struct Buffer {
  int dev;
  int blockno;
  int locked;
  bool dirty;

  Buffer(int d = -1, int b = -1)
      : dev(d), blockno(b), locked(false), dirty(false) {}
};

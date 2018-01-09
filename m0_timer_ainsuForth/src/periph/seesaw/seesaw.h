// Tue Jan  9 19:53:04 UTC 2018
// 4737-a0c-00s- // +cribs +freq +fade

// Tue Jan  9 04:30:43 UTC 2018
// 4737-a0c-00j- // +cribs +freq +fade

// Mon Jan  8 22:01:58 UTC 2018
// 4737-a0c-00f- // +cribs +dump_cribs +freq

// Mon Jan  8 21:51:45 UTC 2018
// 4737-a0c-00e- // +cribs


extern const char fade_str[]; // = "fade";
extern void _fade(void);

// unused:
extern const char freq_str[]; // = "freq";
extern void _freq(void);

// externals .. must tell the compiler about them for local use:
extern void dStack_push(cell_t value);
extern cell_t dStack_pop(void);

#include "rk.h"

static struct termios orig_termios;

int
rk_mytermsave (void)
{
  return tcgetattr (STDIN_FILENO, &orig_termios);
}

int
rk_mytermrestore (void)
{
  return tcsetattr (STDIN_FILENO, TCSAFLUSH, &orig_termios);
}

int
rk_mytermregime (int regime, int vtime, int vmin, int echo, int sigint)
{
  struct termios newt;
  if (tcgetattr (STDIN_FILENO, &newt) < 0)
    return -1;

  if (regime)
    {
      newt.c_lflag &= ~ICANON;
      newt.c_cc[VTIME] = vtime;
      newt.c_cc[VMIN] = vmin;
    }
  else
    {
      newt.c_lflag |= ICANON;
    }

  if (echo)
    newt.c_lflag |= ECHO;
  else
    newt.c_lflag &= ~ECHO;

  if (sigint)
    newt.c_lflag |= ISIG;
  else
    newt.c_lflag &= ~ISIG;

  return tcsetattr (STDIN_FILENO, TCSAFLUSH, &newt);
}

enum keys
rk_charToKey (char c)
{
  if (c >= 'A' && c <= 'Z')
    return (enum keys) (KEY_A + (c - 'A'));
  if (c >= 'a' && c <= 'z')
    return (enum keys) (KEY_a + (c - 'a'));
  if (c >= '0' && c <= '9')
    return (enum keys) (KEY_0 + (c - '0'));
  if (c == '+')
    return KEY_PLUS;
  if (c == '-')
    return KEY_MINUS;
  return KEY_UNKNOWN;
}

int
rk_readkey (enum keys *key)
{
  char seq[6] = { 0 };
  int n;

  do
    {
      n = read (STDIN_FILENO, &seq[0], 1);
    }
  while (n == 0);

  if (n <= 0)
    return -1;

  if (seq[0] == '\e')
    {
      int r = read (STDIN_FILENO, &seq[1], 1);
      if (r <= 0)
        {
          *key = KEY_ESC;
          return 0;
        }

      int i = 2;
      while (i < 5)
        {
          r = read (STDIN_FILENO, &seq[i], 1);
          if (r <= 0)
            break;
          i++;
        }

      if (seq[1] == '[')
        {
          if (seq[2] == 'A')
            {
              *key = KEY_UP;
              return 0;
            }
          if (seq[2] == 'B')
            {
              *key = KEY_DOWN;
              return 0;
            }
          if (seq[2] == 'C')
            {
              *key = KEY_RIGHT;
              return 0;
            }
          if (seq[2] == 'D')
            {
              *key = KEY_LEFT;
              return 0;
            }
          if (seq[2] == '1' && seq[3] == '5')
            {
              *key = KEY_F5;
              return 0;
            }
          if (seq[2] == '1' && seq[3] == '7')
            {
              *key = KEY_F6;
              return 0;
            }
        }

      *key = KEY_UNKNOWN;
      return 0;
    }
  else if (seq[0] == '\n' || seq[0] == '\r')
    {
      *key = KEY_ENTER;
      return 0;
    }
  else
    {
      *key = rk_charToKey (seq[0]);
      return 0;
    }
}

const char *
rk_keyToString (enum keys key)
{
  static char buf[2] = { 0, 0 };

  if (key >= KEY_A && key <= KEY_Z)
    return (char[]){ 'A' + (key - KEY_A), 0 };
  if (key >= KEY_a && key <= KEY_z)
    return (char[]){ 'a' + (key - KEY_a), 0 };
  if (key >= KEY_0 && key <= KEY_9)
    return (char[]){ '0' + (key - KEY_0), 0 };
  if (key == KEY_PLUS)
    return "+";
  if (key == KEY_MINUS)
    return "-";

  switch (key)
    {
    case KEY_UP:
      return "UP";
    case KEY_DOWN:
      return "DOWN";
    case KEY_LEFT:
      return "LEFT";
    case KEY_RIGHT:
      return "RIGHT";
    case KEY_F5:
      return "F5";
    case KEY_F6:
      return "F6";
    case KEY_ESC:
      return "ESC";
    case KEY_ENTER:
      return "ENTER";
    case KEY_UNKNOWN:
      return "UNKNOWN";
    default:
      snprintf (buf, sizeof (buf), "?");
      return buf;
    }
}

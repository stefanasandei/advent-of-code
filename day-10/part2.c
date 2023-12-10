/*
 *  Part 2 is not done!
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void err_n_die(bool cond, char *msg) {
  if (!cond)
    return;
  fprintf(stderr, "%s\n", msg);
  exit(EXIT_FAILURE);
}

typedef struct {
  int x, y;
} coord_t;

typedef struct {
  int front, rear;
  coord_t data[16384];
} queue_t;

coord_t coord_make() {
  coord_t c;
  c.x = 0;
  c.y = 0;
  return c;
}

void queue_make(queue_t *queue) {
  queue->front = -1;
  queue->rear = -1;
}

bool queue_empty(queue_t *queue) {
  return (queue->front == -1 || queue->front > queue->rear);
}

void queue_push(queue_t *queue, coord_t item) {
  if (queue->front == -1)
    queue->front = 0;

  queue->data[++queue->rear] = item;
}

coord_t queue_pop(queue_t *queue) {
  if (queue_empty(queue))
    return coord_make();

  coord_t dequeued = queue->data[queue->front];
  queue->front++;

  return dequeued;
}

coord_t queue_top(queue_t *queue) {
  if (queue->front == -1)
    return coord_make();
  return queue->data[queue->front];
}

const char pipes[] = {'|', '-', 'L', 'J', '7', 'F'};

char dx[128][4];
char dy[128][4];

char line[1024], map[1024][1024];
int sum, size, m, visited[1024][1024];
queue_t queue;

void init_dirs();

bool is_pipe(char c) {
  for (int i = 0; i < 6; i++)
    if (c == pipes[i])
      return true;
  return false;
}

bool inside(int x, int y) { return x >= 0 && x < m && y >= 0 && y < size; }

// the current pipe can connect to (x, y) so we need to check if (x, y) can go
// to the current pipe
bool can_connect(coord_t crt, int x, int y) {
  char pipe = map[x][y];

  for (int k = 0; k < 2; k++) {
    int nx = x + dx[(int)pipe][k];
    int ny = y + dy[(int)pipe][k];

    if (nx == crt.x && ny == crt.y)
      return true;
  }

  return false;
}

int lee(coord_t start) {
  int _max = 0;

  queue_make(&queue);

  queue_push(&queue, start);
  visited[start.x][start.y] = 1;

  while (!queue_empty(&queue)) {
    coord_t top = queue_top(&queue);
    char pipe = map[top.x][top.y];

    for (int k = 0; k < 2; k++) {
      int x = top.x + dx[(int)pipe][k];
      int y = top.y + dy[(int)pipe][k];

      if (!inside(x, y))
        continue;

      if (is_pipe(map[x][y]) && visited[x][y] == 0 && can_connect(top, x, y)) {
        coord_t new_coords = {.x = x, .y = y};
        visited[x][y] = visited[top.x][top.y] + 1;
        _max = (visited[x][y] > _max ? visited[x][y] : _max);
        queue_push(&queue, new_coords);
      }
    }

    (void)queue_pop(&queue);
  }

  /*for (int i = 0; i < size; i++) {
    for (int j = 0; j < m; j++)
      printf("%*d ", 2, visited[i][j]);
    printf("\n");
  }
  printf("\n");*/

  return _max;
}

void solve(void) {
  int _max = 0;
  m = strlen(map[0]) - 1;

  // find the starting position
  coord_t start;

  for (int i = 0; i < size; i++) {
    for (int j = 0; j < m; j++) {
      if (map[i][j] == 'S') {
        start.x = i;
        start.y = j;
        break;
      }
    }
  }

  const int ndx[] = {0, 0, 1, -1};
  const int ndy[] = {-1, 1, 0, 0};

  for (int k = 0; k < 4; k++) {
    int x = start.x + ndx[k];
    int y = start.y + ndy[k];

    if (!is_pipe(map[x][y]))
      continue;

    if (!can_connect(start, x, y))
      continue;

    coord_t new_start = {.x = x, .y = y};
    int dist = lee(new_start);

    _max = (dist > _max ? dist : _max);
  }

  float halfway = (float)_max / 2.0f;
  printf("%d\n", (int)halfway + 1);
}

int main(void) {
  FILE *fp = fopen("./day-10/input.txt", "r");
  err_n_die(fp == NULL, "Couldn't find the input file.");

  init_dirs();

  while (fgets(line, sizeof(line), fp) != NULL) {
    strcpy(map[size++], line);
  }

  solve();

  fclose(fp);
  return 0;
}

void init_dirs() {
  dy['|'][0] = 0;
  dx['|'][0] = 1; // south

  dy['|'][1] = 0;
  dx['|'][1] = -1; // north

  dy['-'][0] = -1;
  dx['-'][0] = 0; // west

  dy['-'][1] = 1;
  dx['-'][1] = 0; // east

  dy['L'][0] = 0;
  dx['L'][0] = -1; // north

  dy['L'][1] = 1;
  dx['L'][1] = 0; // east

  dy['J'][0] = 0;
  dx['J'][0] = -1; // north

  dy['J'][1] = -1;
  dx['J'][1] = 0; // west

  dy['7'][0] = 0;
  dx['7'][0] = 1; // south

  dy['7'][1] = -1;
  dx['7'][1] = 0; // west

  dy['F'][0] = 0;
  dx['F'][0] = 1; // south

  dy['F'][1] = 1;
  dx['F'][1] = 0; // east
}

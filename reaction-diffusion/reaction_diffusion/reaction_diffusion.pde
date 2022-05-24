var grid = [];



void setup() {
  size(200, 200);
  for(var x = 0; x< width; x++){
    grid[x] = [];
    for(var y = 0; y< height; y++){
      grid[x][y] = new Cell(x, y);
    }
  }
}

void draw() {
  
}

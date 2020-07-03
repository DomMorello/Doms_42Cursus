# Cub3d (42 school)

## Subject
> the program is “realistic” 3D graphical
representation of the inside of a maze from a
first person perspective by using the algorithm of ray casting.<br>

> 이 프로그램은 레이캐스팅이라는 알고리즘을 사용하여 미로(맵)안에서 일인칭 시점으로 보여지는 모습들을 3D 그래픽으로 나타냅니다.

## Compile
the program works only in MacOS
- `git clone https://github.com/DomMorello/cub3d.git`
- `cd cub3d`
- `make`
- `./cub3d ./map/valid_basic.cub`
- if you want to save a screenshot `./cub3d ./map/valid_basic.cub --save`<br>

이 프로그램은 맥 OS환경에서만 실행 가능합니다.<br>
- 화면에 렌더링되는 첫 이미지를 캡쳐하려면 `./cub3d ./map/valid_basic.cub --save` 로 실행하시면 됩니다. 
## Requirements
- the program takes as a first arguement a scene description file with the .cub extension
- different wall textures(north, south, west, east)
- display item(sprite) instead of wall
- different floor and ceiling colors(RGB) 
- when you give the second arguement as "--save" then the program creates screenshot in bmp file format as "capture.bmp"
- right and left arrow key to look right and left
- W,A,S and D key to move forward, left backwar and right
- ESC key to quit the program
- if the resolution information in the map file is bigger(smaller) than maximum(minimal) resolution it will be adjusted to maximum(minimal) resolution
- clicking on the red cross on the window's frame close the window and quit the program cleanly
<br><br>
- 프로그램을 실행할 때 맵을 묘사하는 .cub 확장자를 가진 파일을 첫 번째 인자로 받습니다.
- 동,서,남,북 각기 다른 벽 이미지로 묘사
- 벽 대신에 아이템(물건) 등을 렌더링
- 천장과 바닥을 서로 다른 색으로 묘사
- 프로그램을 실행할 때 두 번째 인자로 "--save" 를 입력하면 처음 렌더링되는 화면을 캡쳐해서 "capture.bmp" 파일을 루트폴더에 생성합니다. 
- 오른쪽, 왼쪽 방향키를 누르면 시선을 오른쪽, 왼쪽으로 돌립니다.
- W,A,S,D 키를 누르면 앞, 왼쪽, 뒤, 오른쪽으로 일인칭 시점이 움직입니다.
- ESC 키를 누르면 프로그램을 종료합니다.
- 첫 번째 인자로 받는 맵 묘사 파일안에 해상도 정보가 정해진 해상도보다 크거나 작으면 최고 해상도와 최저 해상도로 조정됩니다.
- 프로그램이 실행되면 3D맵을 묘사하는 윈도우 창이 뜨는데 이 창의 빨간 X버튼을 누르면 프로그램이 정상적으로 종료됩니다.

## Scene description file (.cub)
- The map must be composed of only 4 possible characters: 0 for an empty
space, 1 for a wall, 2 for an item and N,S,E or W for the player’s start
position and spawning orientation
- The map must be closed/surrounded by walls, if not the program returns
an error
- Except for the map content, each type of element can be separated by one or
more empty line(s)
- Except for the map content which always has to be the last, each type of
element can be set in any order in the file
- Except for the map, each type of information from an element can be separated
by one or more space(s)
- The map must be parsed as it looks like in the file. Spaces are a valid part of
the map
- Each element (except the map) first information is the type identifier (composed by one or two character(s)), followed by all specific informations for each
object in a strict order such as :
#### Resolution
> R   230   540
- identifier: R
- x render size
- y render size
#### Textures
>NO ./textures/wood.xpm<br>
>S ./textures/barrel.xpm
- identifier: NO, SO, WE, EA, S
- path to the texure
- if you want to see the texture on the floor and ceiling instead of just RGB color, you can input the filepath to the texture like "F ./texture/redbrick.xpm"
#### Color
> F 234 53 123
- identifier: F C
- RGB colors in range [0, 255]: 0, 255, 255

If any misconfiguration of any kind is encountered in the file, the program returns error
<br><br>
- 맵에서 가능한 문자는 4개 입니다. 0은 빈 공간, 1은 벽, 2는 아이템(물건)을 말하고 N,S,E,W는 플레이어가 바라보는 방향과 플레이어의 최초 위치를 말합니다.
- 맵은 벽으로 둘러쌓여 있어야 하고 그렇지 않으면 에러를 반환합니다.
- 맵 정보를 묘사한 부분을 제외하고는 다른 요소들은 복수의 개행으로 나눠져도 무방합니다.
- 맵 정보는 항상 파일의 끝에 위치해야하고 다른 정보들은 맵 정보 위에만 위치해있다면 그 순서는 섞여있어도 무방합니다.
- 맵 정보를 묘사한 부분을 제외하고는 다른 요소들은 복수의 빈 공간(띄어쓰기)으로 나눠져도 무방합니다.
- 맵 정보를 묘사한 부분은 그 규칙에 따라서 프로그램에 렌더링 돼야 하고 맵 정보에서 빈 공간(띄어쓰기)는 유효합니다.
- 맵 정보를 묘사한 부분을 제외하고 다른 요소들의 첫 번째 문자(한 글자 또는 두 글자)는 그 정보가 무엇인지 알려주는 식별자입니다. 그 이후에 나오는 정보는 아래와 같습니다. 또한 식별자 + 정보 이 순서여아만 합니다.

#### 해상도
>NO ./textures/wood.xpm<br>
>S ./textures/barrel.xpm
- 식별자: NO, SO, WE, EA, S
- 텍스쳐 파일의 경로
- 천장과 바닥에 RGB 색상 말고 텍스쳐를 표현하고 싶으면 파일에 "F ./texture/redbrick.xpm"과 같이 이미지 파일의 경로를 입력해주면 됩니다. 
#### 색
> F 234 53 123
- 식별자: F C
- RGB 색생. 각 RGB 컬러의 범위는 0 ~ 255: 예) 0, 255, 255

위 규칙에 맞지 않는 형식이 맵에 포함돼있다면 프로그램은 에러를 반환합니다.

## reference
- Raycasting algorithm in c++ (https://lodev.org/cgtutor/raycasting.html)<br>
- Raycasting basics in JavaScript (https://courses.pikuma.com/courses/raycasting)<br>
- Raycasting Tutorial (https://permadi.com/1996/05/ray-casting-tutorial-table-of-contents/)<br>

#### Contact: zuzudnf@gmail.com
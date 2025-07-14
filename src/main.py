import pygame
from sharedVars import *
from progInfo import *
from entity import *
from random import *
from highScore import *
clock = pygame.time.Clock()
screen = pygame.display.set_mode((RENDER_WIDTH, RENDER_HEIGHT))
running = true
timerStart = false
randomColors = [
[ 0x00, 0x00, 0xAA ],
[ 0x00, 0xAA, 0x00 ],
[ 0x00, 0xAA, 0xAA ],
[ 0xAA, 0x00, 0x00 ],
[ 0xAA, 0x00, 0xAA ],
[ 0xAA, 0x55, 0x00 ],
[ 0x55, 0x55, 0xFF ],
[ 0x55, 0xFF, 0x55 ],
[ 0x55, 0xFF, 0xFF ],
[ 0xFF, 0x55, 0x55 ],
[ 0xFF, 0x55, 0xFF ],
[ 0xFF, 0xFF, 0x55 ]
]
oldRandomColor = 13
randomColor = 13
level = 1
blockCount = 0
timer = 0
score = 0
highScore = 0
player = NULL
blocks = []
pygame.font.init()
font = pygame.font.SysFont(
    pygame.font.get_default_font(),
    FONT_HEIGHT
    )
def lessThanSet(var, value):
    if (var < value):
        return value
    else:
        return var
def generateLevel(level):
    global oldRandomColor
    global randomColor
    global blockCount
    global blocks
    blockCount = 0
    if (level):
        blockSize = [
        round(RENDER_WIDTH / level),
        round(RENDER_HEIGHT / (level * 1.5))
        ]
        blockSize[0] = lessThanSet(blockSize[0], 1)
        blockSize[1] = lessThanSet(blockSize[1], 1)
        for y in range(level):
            oldRandomColor = randomColor
            while (randomColor == oldRandomColor):
                randomColor = random_get()
            for x in range(level):
                if (
                    (x * blockSize[0] < RENDER_WIDTH) and
                    (y * blockSize[1] < RENDER_HEIGHT)
                    ):
                    blockCount += 1
                    blocks.append(entity(
                            randomColors[randomColor][0],
                            randomColors[randomColor][1],
                            randomColors[randomColor][2],
                            ENTITY_DIR_NONE,
                            blockSize[0], blockSize[1],
                            x * blockSize[0], y * blockSize[1],
                            0,
                            true
                            ))
    return
def init():
    global level
    global timer
    global player
    if (timer + (level * 35) > 0xFFFF):
        timer = 0xFFFF
    else:
        timer += level * 35
    player = entity(
        0xFF, 0xFF, 0xFF,
        ENTITY_DIR_NONE,
        PLAYER_WIDTH, PLAYER_HEIGHT,
        PLAYER_START_X, PLAYER_START_Y,
        PLAYER_SPEED,
        true
        )
    generateLevel(level)
    return
def reset():
    global timerStart
    global level
    global timer
    global score
    global blocks
    timer = 0
    level = 1
    score = 0
    timerStart = false
    for block in blocks:
        block.visible = false
    init()
    return
def draw():
    global level
    global blockCount
    global timer
    global score
    global highScore
    clock.tick(MAX_FPS)
    if (blockCount < 1):
        if (score + (timer / 4) > 0xFFFFFFFF):
            score = 0xFFFFFFFF
        else:
            score += round(timer / 4)
        if (level < MAX_BLOCKS):
            level += 1
        init()
    screen.fill((0x00, 0x00, 0x00))
    if (player.position[1] <= SCREEN_EDGE_UP):
        player.direction = ENTITY_DIR_DOWN
        player.position[1] = SCREEN_EDGE_UP
    elif (player.position[1] >= SCREEN_EDGE_DOWN):
        player.direction = ENTITY_DIR_UP
        player.position[1] = SCREEN_EDGE_DOWN
    elif (player.position[0] <= SCREEN_EDGE_LEFT):
        player.direction = ENTITY_DIR_RIGHT
        player.position[0] = SCREEN_EDGE_LEFT
    elif (player.position[0] >= SCREEN_EDGE_RIGHT):
        player.direction = ENTITY_DIR_LEFT
        player.position[0] = SCREEN_EDGE_RIGHT
    player.draw(screen, true)
    for block in blocks:
        if (block.visible):
            block.draw(screen, false)
            if (player.collision(block)):
                block.visible = false
                blockCount -= 1
                score += 10
    screen.blit(
        font.render(str(timer), false, (0xFF, 0xFF, 0xFF)),
        (0, RENDER_HEIGHT - (FONT_HEIGHT * 4))
        )
    screen.blit(
        font.render(str(score), false, (0xFF, 0xFF, 0xFF)),
        (0, RENDER_HEIGHT - (FONT_HEIGHT * 2))
        )
    screen.blit(
        font.render(str(highScore), false, (0xFF, 0xFF, 0xFF)),
        (0, RENDER_HEIGHT - FONT_HEIGHT)
        )
    if (timerStart):
        timer -= 1
    if (timer < 1):
        if (score > highScore):
            highScore = score
            hssImpl_set(highScore)
        reset()
    pygame.display.update()
    return
def main():
    global running
    global timerStart
    global player
    global highScore
    hssImpl_open()
    highScore = hssImpl_get()
    init()
    pygame.init()
    pygame.display.set_caption(PROGRAM_NAME + " v" + PROGRAM_VERSION)
    while (running):
        for event in pygame.event.get():
            if (event.type == pygame.KEYDOWN):
                random_increase()
                if (event.key == pygame.K_UP):
                    timerStart = true
                    player.direction = ENTITY_DIR_UP
                if (event.key == pygame.K_DOWN):
                    timerStart = true
                    player.direction = ENTITY_DIR_DOWN
                if (event.key == pygame.K_LEFT):
                    timerStart = true
                    player.direction = ENTITY_DIR_LEFT
                if (event.key == pygame.K_RIGHT):
                    timerStart = true
                    player.direction = ENTITY_DIR_RIGHT
                if (event.key == pygame.K_RETURN):
                    reset()
                if (event.key == pygame.K_ESCAPE):
                    running = false
            if (event.type == pygame.QUIT):
                running = 0
        draw()
    pygame.quit()
    hssImpl_close()
    return
main()

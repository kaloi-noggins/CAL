import os
import sys
import random
import math
import time
import pygame
from pygame.locals import *



pygame.init()

FPS = 60
SCREEN_WIDTH = 800
SCREEN_HEIGHT = 600
ENEMY_SPEED = 2 
WHITE = (255, 255, 255)

DISPLAYSURF = pygame.display.set_mode((SCREEN_WIDTH, SCREEN_HEIGHT))
DISPLAYSURF.fill(WHITE)
pygame.display.set_caption("O Fugitivo")

player_image = pygame.transform.scale(pygame.image.load("playerBlue.png"), (75, 75))
enemy_image = pygame.transform.scale(pygame.image.load("playerRed.png"), (75, 75))

class Player(pygame.sprite.Sprite):
    def __init__(self):
        super().__init__()
        self.image = player_image
        self.rect = self.image.get_rect()
        self.rect.center = (160, 520)

    def update(self):
        pressed_keys = pygame.key.get_pressed()
        if pressed_keys[K_UP] and self.rect.top > 0:
            self.rect.move_ip(0, -5)
        if pressed_keys[K_DOWN] and self.rect.bottom < SCREEN_HEIGHT:
            self.rect.move_ip(0, 5)
        if pressed_keys[K_LEFT] and self.rect.left > 0:
            self.rect.move_ip(-5, 0)
        if pressed_keys[K_RIGHT] and self.rect.right < SCREEN_WIDTH:
            self.rect.move_ip(5, 0)

    def getPos(self):
        return self.rect.center

class Enemy(pygame.sprite.Sprite):
    def __init__(self):
        super().__init__()
        self.image = enemy_image
        self.rect = self.image.get_rect()
        self.rect.center = (random.randint(0, SCREEN_WIDTH), random.randint(0, SCREEN_HEIGHT))

    def move(self, player):
        player_x, player_y = player.getPos()

        dx = player_x - self.rect.centerx
        dy = player_y - self.rect.centery

        length = math.sqrt(dx**2 + dy**2)
        if length != 0:
            dx /= length
            dy /= length

        self.rect.x += dx * ENEMY_SPEED
        self.rect.y += dy * ENEMY_SPEED

player = Player()
enemies = [Enemy() for _ in range(3)]

clock = pygame.time.Clock()
while True:
    for event in pygame.event.get():
        if event.type == QUIT:
            pygame.quit()
            sys.exit()

    player.update()
    for enemy in enemies:
        enemy.move(player)

    # Check for collision between player and enemies
    if any(enemy.rect.colliderect(player.rect) for enemy in enemies):
        time.sleep(2)
        player.rect.center = (160, 520)
        enemies = [Enemy() for _ in range(3)]  # Reset enemies

    DISPLAYSURF.fill(WHITE)
    DISPLAYSURF.blit(player.image, player.rect)
    for enemy in enemies:
        DISPLAYSURF.blit(enemy.image, enemy.rect)

    pygame.display.update()
    clock.tick(FPS)

//
// Created by efry on 3/11/2017.
//

#include <SDL_system.h>
#include "video.h"
#include "palette.h"
#include "tile.h"
#include "input.h"

SDL_Window *window;
SDL_Renderer *renderer;
SDL_Texture *texture;
SDL_Surface *surface;
SDL_Surface *windowSurface;

void display_fullscreen_image(uint8 image_number)
{

}

void fade_to_black_speed_3()
{
    fade_to_black(3);
}

bool video_init()
{
    window = SDL_CreateWindow("Cosmo Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH*2, SCREEN_HEIGHT*2, 0);
    if(window == NULL)
    {
        printf("Error: creating SDL Window. %s\n", SDL_GetError());
        return false;
    }

    renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED );
    if(renderer == NULL)
    {
        printf("Error: creating render. %s\n", SDL_GetError());
        return false;
    }

    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, SCREEN_WIDTH, SCREEN_HEIGHT);
    if(texture == NULL)
    {
        printf("Error: creating texture. %s\n", SDL_GetError());
        return false;
    }

    surface = SDL_CreateRGBSurface(0, SCREEN_WIDTH, SCREEN_HEIGHT, 8, 0, 0, 0, 0);
    if(surface == NULL)
    {
        printf("Error: creating indexed surface. %s\n", SDL_GetError());
        return false;
    }

    set_palette_on_surface(surface);

    windowSurface = SDL_CreateRGBSurface(0,
                           surface->w, surface->h,
                           32, 0, 0, 0, 0);
    if(windowSurface == NULL)
    {
        printf("Error: creating window surface. %s\n", SDL_GetError());
        return false;
    }

    SDL_RenderSetLogicalSize( renderer, SCREEN_WIDTH, SCREEN_HEIGHT );
    SDL_SetRenderDrawColor( renderer, 0, 0, 0, 255 );
    SDL_RenderClear( renderer );
    SDL_RenderPresent( renderer);

    return true;
}

void video_shutdown()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}

void video_update()
{
    SDL_BlitSurface(surface, NULL, windowSurface, NULL);

    void *pixels;
    int pitch;
    SDL_LockTexture(texture, NULL, &pixels, &pitch);
    SDL_ConvertPixels(windowSurface->w, windowSurface->h,
                      windowSurface->format->format,
                      windowSurface->pixels, windowSurface->pitch,
                      SDL_PIXELFORMAT_RGBA8888,
                      pixels, pitch);
    SDL_UnlockTexture(texture);

    /* Make the modified texture visible by rendering it */
    SDL_RenderCopy(renderer, texture, NULL, NULL);

    /*
     * Update the screen with any rendering performed since the
     * previous call
     */
    SDL_RenderPresent(renderer);
}

void video_draw_tile(Tile *tile, uint16 x, uint16 y)
{
    uint8 *pixel = &surface->pixels[x + y * SCREEN_WIDTH];
    uint8 *tile_pixel = tile->pixels;
    if(tile->type == SOLID)
    {
        for(int i=0;i<TILE_HEIGHT;i++)
        {
            memcpy(pixel, tile_pixel, TILE_WIDTH);
            pixel += SCREEN_WIDTH;
            tile_pixel += TILE_WIDTH;
        }
    }
    else
    {
        for(int i=0;i<TILE_HEIGHT;i++)
        {
            for(int j=0;j<TILE_WIDTH;j++)
            {
                if(*tile_pixel != TRANSPARENT_COLOR)
                {
                    *pixel = *tile_pixel;
                }
                pixel++;
                tile_pixel++;
            }
            pixel += SCREEN_WIDTH - TILE_WIDTH;
        }
    }
}

void video_draw_tile_solid_white(Tile *tile, uint16 x, uint16 y)
{
    uint8 *pixel = &surface->pixels[x + y * SCREEN_WIDTH];
    uint8 *tile_pixel = tile->pixels;
    if(tile->type == SOLID)
    {
        for(int i=0;i<TILE_HEIGHT;i++)
        {
            memcpy(pixel, tile_pixel, TILE_WIDTH);
            pixel += SCREEN_WIDTH;
            tile_pixel += TILE_WIDTH;
        }
    }
    else
    {
        for(int i=0;i<TILE_HEIGHT;i++)
        {
            for(int j=0;j<TILE_WIDTH;j++)
            {
                if(*tile_pixel != TRANSPARENT_COLOR)
                {
                    *pixel = 0xf;
                }
                pixel++;
                tile_pixel++;
            }
            pixel += SCREEN_WIDTH - TILE_WIDTH;
        }
    }
}

void video_draw_tile_with_clip_rect(Tile *tile, uint16 x, uint16 y, uint16 clip_x, uint16 clip_y, uint16 clip_w, uint16 clip_h)
{
    uint16 tx = 0;
    uint16 ty = 0;
    uint16 w = TILE_WIDTH;
    uint16 h = TILE_HEIGHT;

    if (x + w < clip_x ||
        y + h < clip_y ||
        x > clip_x + clip_w ||
        y > clip_y + clip_h)
    {
        return;
    }

    if (x < clip_x)
    {
        tx = (clip_x - x);
        w = TILE_WIDTH - tx;
        x = clip_x;
    }

    if (x + w > clip_x + clip_w)
    {
        w -= ((x + w) - (clip_x + clip_w));
    }

    if (y < clip_y)
    {
        ty = (clip_y - y);
        h = TILE_HEIGHT - ty;
        y = clip_y;
    }

    if (y + h > clip_y + clip_h)
    {
        h -= ((y + h) - (clip_y + clip_h));
    }

    uint8 *pixel = &surface->pixels[x + y * SCREEN_WIDTH];
    uint8 *tile_pixel = &tile->pixels[tx + ty * TILE_WIDTH];
        for(int i=0;i<h;i++)
        {
            for(int j=0; j < w; j++)
            {
                if(tile_pixel[j] != TRANSPARENT_COLOR)
                {
                    pixel[j] = tile_pixel[j];
                }
            }
            pixel += SCREEN_WIDTH;
            tile_pixel += TILE_WIDTH;
        }
}

void video_draw_tile_flipped(Tile *tile, uint16 x, uint16 y)
{
    uint8 *pixel = &surface->pixels[x + (y+TILE_HEIGHT-1) * SCREEN_WIDTH];
    uint8 *tile_pixel = tile->pixels;
    for(int i=0;i<TILE_HEIGHT;i++)
    {
        for(int j=0;j<TILE_WIDTH;j++)
        {
            if(*tile_pixel != TRANSPARENT_COLOR)
            {
                *pixel = *tile_pixel;
            }
            pixel++;
            tile_pixel++;
        }
        pixel -= (SCREEN_WIDTH + TILE_WIDTH);
    }
}

void video_update_palette(int palette_index, SDL_Color new_color)
{
    SDL_SetPaletteColors(surface->format->palette, &new_color, palette_index, 1);
}

void fade_to_black(uint16 wait_time)
{
    for(int i=0;i < 16; i++)
    {
        cosmo_wait(wait_time);
        set_palette_color(i, 0);
        video_update();
    }
}

void fade_in_from_black(uint16 wait_time)
{
    int j=0;
    for(int i=0;i < 16; i++)
    {
        if(i == 8)
        {
            j = 8;
        }
        set_palette_color(i, i);
        video_update();
        cosmo_wait(wait_time);
    }
}

void fade_in_from_black_with_delay_3()
{
    fade_in_from_black(3);
}

void video_fill_screen_with_black() {
    SDL_Rect rect;
    rect.x=0;
    rect.y=0;
    rect.w=surface->w;
    rect.h=surface->h;
    SDL_FillRect(surface, &rect, 0);
}

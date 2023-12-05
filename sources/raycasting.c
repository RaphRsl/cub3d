/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rroussel <rroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 16:56:46 by toteixei          #+#    #+#             */
/*   Updated: 2023/12/05 19:41:10 by rroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

// void    render_texture_line(int draw_start, int draw_end, int x, double tex_pos, double step, t_cub3d *cub3d, int *texture, int tex_x)
// {
//     int y = 0;
//     int *color = 0;
//     while (y < draw_start)
//     {
//         cub3d->img.addr[y * SCREEN_WIDTH + x] = cub3d->config->c_color[0] << 16 | cub3d->config->c_color[1] << 8 | cub3d->config->c_color[2];
//         y++;
//     }
//     while (y < draw_end)
//     {
//         int tex_y = (int)tex_pos & (cub3d->xpm.tex_height - 1);
//         tex_pos += step;
//         color = texture;
//         cub3d->img.addr[y * SCREEN_WIDTH + x] = color[tex_y * cub3d->xpm.tex_height + tex_x];
//         y++;
//     }
//     while (y < SCREEN_HEIGTH)
//     {
//         cub3d->img.addr[y * SCREEN_WIDTH + x] = cub3d->config->fl_color[0] << 16 | cub3d->config->fl_color[1] << 8 | cub3d->config->fl_color[2];
//         y++;
//     }
// }

void render_texture_line(int draw_start, int draw_end, int x, double tex_pos, double step, t_cub3d *cub3d, void *texture, int tex_x)
{
    int y = 0;
    int *color = NULL;
    
    // Clear the entire column before rendering the new frame
    while (y < SCREEN_HEIGTH)
    {
        // Render floor and ceiling colors
        cub3d->img.addr[y * SCREEN_WIDTH + x] = (y < SCREEN_HEIGTH / 2) ?
            cub3d->config->c_color[0] << 16 | cub3d->config->c_color[1] << 8 | cub3d->config->c_color[2] :
            cub3d->config->fl_color[0] << 16 | cub3d->config->fl_color[1] << 8 | cub3d->config->fl_color[2];

        y++;
    }

    y = draw_start;
    
    while (y < draw_end && y < SCREEN_HEIGTH)
    {
        int tex_y = (int)tex_pos & (cub3d->xpm.tex_height - 1); // Calculate texture Y coordinate

        // Ensure texture coordinates are within the texture boundaries
        if (tex_y < 0)
            tex_y = 0;
        if (tex_y >= cub3d->xpm.tex_height)
            tex_y = cub3d->xpm.tex_height - 1;

        color = (int *)texture; // Cast texture to an int pointer

        // Render the texture pixel onto the screen
        cub3d->img.addr[y * SCREEN_WIDTH + x] = color[tex_y * cub3d->xpm.tex_width + tex_x];

        tex_pos += step; // Move to the next texture position
        y++;
    }
}







void    draw_rays_3d(t_cub3d *cub3d)
{
    // Extracting camera properties
    float   pos_x = cub3d->cam.p_x;
    float   pos_y = cub3d->cam.p_y;
    float   dir_x = cub3d->cam.pd_x;
    float   dir_y = cub3d->cam.pd_y;
    // float   plane_x = cub3d->cam.plane_x;
    // float   plane_y = cub3d->cam.plane_y;
    int     w = SCREEN_WIDTH;
    int     x = 0;
    double fov = cub3d->cam.fov; //changed


    while (x++ < w)
    {
        // Calculate ray direction in camera space
        double camera_x = 2 * x / (double)w - 1;
        // Calculate the angle for the ray direction
        double ray_angle = (2 * x / (double)w - 1) * fov;
        // double angle = atan2(2 * x - w, w) * fov; //changed with above line
        // double ray_dir_x = dir_x + plane_x * cos(angle); //added 3434
        // double ray_dir_y = dir_y + plane_y * sin(angle); //added 3434 
        
        // Calculate the distance to the projection plane (screen)
        // double distance_to_plane = (w / 2) / tan(fov / 2); //added to correct fisheye effect
        // Calculate the correction factor based on the distance from the center of the screen
        // double ray_offset = abs(x - w / 2); // Distance from the center of the screen //added to correct fisheye effect
        // Avoid division by zero (when ray_offset is zero)
        // double epsilon = 0.00001;
        // double correction = distance_to_plane / (ray_offset + epsilon); //added to correct fisheye effect

        // Apply correction to the ray direction vectors
        double ray_dir_x = dir_x * cos(ray_angle) - dir_y * sin(ray_angle); //added 3435
        double ray_dir_y = dir_x * sin(ray_angle) + dir_y * cos(ray_angle); //added 3435

        // Apply perspective correction to maintain aspect ratio of objects
        // ray_dir_x *= correction; //added to correct fisheye effect
        // ray_dir_y *= correction; //added to correct fisheye effect

        // Initialize variables for ray casting
        int map_x = (int)pos_x;
        int map_y = (int)pos_y;

        //distance de la position actuelle du joueur au prochain x ou y
        double side_dist_x;
        double side_dist_y;
        
        double delta_dist_x = sqrt(1 + (ray_dir_y * ray_dir_y) / (ray_dir_x * ray_dir_x));
        double delta_dist_y = sqrt(1 + (ray_dir_x * ray_dir_x) / (ray_dir_y * ray_dir_y));
        double perp_wall_dist;
        int step_x;
        int step_y;
        int hit = 0;
        int side;
        if (ray_dir_x < 0)
        {
            step_x = -1;
            side_dist_x = (pos_x - map_x) * delta_dist_x;
        }
        else
        {
            step_x = 1;
            side_dist_x = (map_x + 1.0 - pos_x) * delta_dist_x;
        }
        if (ray_dir_y < 0)
        {
            step_y = -1;
            side_dist_y = (pos_y - map_y) * delta_dist_y;
        }
        else
        {
            step_y = 1;
            side_dist_y = (map_y + 1.0 - pos_y) * delta_dist_y;
        }
        // Ray casting loop
        while (hit == 0)
        {
            // ... (ray casting logic)
            if (side_dist_x < side_dist_y)
            {
                side_dist_x += delta_dist_x;
                map_x += step_x;
                side = 0;
            }
            else
            {
                side_dist_y += delta_dist_y;
                map_y += step_y;
                side = 1;
            }
            // Detect collision with wall
            if (cub3d->config->map[map_y][map_x] > 0 && cub3d->config->map[map_y][map_x] < 2)
                hit = 1;
        }





        //after detecting collisions with the walls in the map, we calculate the distance to
        //the wall and determining the height to render the wall on the screen        
        /* Calculating Perpendicular Wall Distance:
            The code determines whether the ray hit a vertical (side == 0) or horizontal (side == 1) wall. This is important for wall rendering.
            The variable perp_wall_dist represents the perpendicular distance from the player's position to the wall. It's calculated based on the side where the ray hit.
            If the ray hits a vertical wall (side == 0), it calculates perp_wall_dist using the difference between side_dist_x and delta_dist_x. Similarly, if it hits a horizontal wall, it uses side_dist_y and delta_dist_y. */
        if (side == 0)
            perp_wall_dist = (side_dist_x - delta_dist_x);
        else
            perp_wall_dist = (side_dist_y - delta_dist_y);
        /* Determining Line Height for Wall Rendering:
            line_height is calculated as the height of the wall on the screen. It's inversely proportional to perp_wall_dist. Closer walls appear taller, while farther walls appear shorter.
            draw_start and draw_end define the range of the wall's height to be rendered on the screen. These values specify where the wall starts and ends vertically on the screen. */

double wall_height = SCREEN_HEIGTH / perp_wall_dist;

// Apply perspective correction for wall heights
// This could involve additional factors like distance, fov (field of view), etc.
// Experiment with different formulas for better perspective correction
wall_height *= cos(fabs(camera_x)); // Applying a simple correction factor

int line_height = (int)wall_height;

        // int line_height = (int)(SCREEN_HEIGTH / perp_wall_dist);
        /* Adjusting Render Limits:
            The code ensures that draw_start and draw_end values fit within the screen's height (SCREEN_HEIGTH). If draw_start is negative (outside the screen), it's adjusted to start at the top of the screen (0). Similarly, if draw_end exceeds the screen's height, it's adjusted to the screen's bottom boundary.
            After these calculations, the code continues to the texture mapping and rendering phase, using the calculated values (draw_start, draw_end, etc.) to render the wall texture within the specified screen area corresponding to the detected wall.
        */
        int draw_start = (-line_height / 2) + (SCREEN_HEIGTH / 2);
        if (draw_start < 0)
            draw_start = 0;
        int draw_end = (line_height / 2) + (SCREEN_HEIGTH / 2);
        if (draw_end >= SCREEN_HEIGTH)
            draw_end = SCREEN_HEIGTH - 1;
        
        // Calculate texture mapping
        double wall_x;
        if (side == 0)
            wall_x = pos_y + perp_wall_dist * ray_dir_y;
        else
            wall_x = pos_x + perp_wall_dist * ray_dir_x;
        wall_x -= floor(wall_x);
        int tex_x = (int)(wall_x * (double)cub3d->xpm.tex_width);
        if (side == 0 && ray_dir_x > 0)
            tex_x = cub3d->xpm.tex_width - tex_x - 1;
        if (side == 1 && ray_dir_y < 0)
            tex_x = cub3d->xpm.tex_width - tex_x - 1;
        // Render the textured line on the screen
        double step = 1.0 * cub3d->xpm.tex_height / line_height;
        double tex_pos = (draw_start - SCREEN_HEIGTH / 2 + line_height / 2) * step;
        if (side == 1 && ray_dir_y > 0)
            render_texture_line(draw_start, draw_end, x, tex_pos, step, cub3d, cub3d->xpm.s_tex_adrr, tex_x);
        else if (side == 1 && ray_dir_y < 0)
            render_texture_line(draw_start, draw_end, x, tex_pos, step, cub3d, cub3d->xpm.n_tex_adrr, tex_x);
        else if (side == 0 && ray_dir_x > 0)
            render_texture_line(draw_start, draw_end, x, tex_pos, step, cub3d, cub3d->xpm.e_tex_adrr, tex_x);
        else
            render_texture_line(draw_start, draw_end, x, tex_pos, step, cub3d, cub3d->xpm.w_tex_adrr, tex_x);
        // Update 'x' to proceed to the next column
    }
}





//--------------TO KEEP-----------------



// void    draw_rays_3d(t_cub3d *cub3d)
// {
//     // Extracting camera properties
//     float   pos_x = cub3d->cam.p_x;
//     float   pos_y = cub3d->cam.p_y;
//     float   dir_x = cub3d->cam.pd_x;
//     float   dir_y = cub3d->cam.pd_y;
//     // float   plane_x = cub3d->cam.plane_x;
//     // float   plane_y = cub3d->cam.plane_y;
//     int     w = SCREEN_WIDTH;
//     int     x = 0;
//     double fov = cub3d->cam.fov; //changed


//     while (x++ < w)
//     {
//         // Calculate ray direction in camera space
//         double camera_x = 2 * x / (double)w - 1;
//         // Calculate the angle for the ray direction
//         double ray_angle = (2 * x / (double)w - 1) * fov;
//         // double angle = atan2(2 * x - w, w) * fov; //changed with above line
//         // double ray_dir_x = dir_x + plane_x * cos(angle); //added 3434
//         // double ray_dir_y = dir_y + plane_y * sin(angle); //added 3434 
        
//         // Calculate the distance to the projection plane (screen)
//         // double distance_to_plane = (w / 2) / tan(fov / 2); //added to correct fisheye effect
//         // Calculate the correction factor based on the distance from the center of the screen
//         // double ray_offset = abs(x - w / 2); // Distance from the center of the screen //added to correct fisheye effect
//         // Avoid division by zero (when ray_offset is zero)
//         // double epsilon = 0.00001;
//         // double correction = distance_to_plane / (ray_offset + epsilon); //added to correct fisheye effect

//         // Apply correction to the ray direction vectors
//         double ray_dir_x = dir_x * cos(ray_angle) - dir_y * sin(ray_angle); //added 3435
//         double ray_dir_y = dir_x * sin(ray_angle) + dir_y * cos(ray_angle); //added 3435

//         // Apply perspective correction to maintain aspect ratio of objects
//         // ray_dir_x *= correction; //added to correct fisheye effect
//         // ray_dir_y *= correction; //added to correct fisheye effect

//         // Initialize variables for ray casting
//         int map_x = (int)pos_x;
//         int map_y = (int)pos_y;

//         //distance de la position actuelle du joueur au prochain x ou y
//         double side_dist_x;
//         double side_dist_y;
        
//         double delta_dist_x = sqrt(1 + (ray_dir_y * ray_dir_y) / (ray_dir_x * ray_dir_x));
//         double delta_dist_y = sqrt(1 + (ray_dir_x * ray_dir_x) / (ray_dir_y * ray_dir_y));
//         double perp_wall_dist;
//         int step_x;
//         int step_y;
//         int hit = 0;
//         int side;
//         if (ray_dir_x < 0)
//         {
//             step_x = -1;
//             side_dist_x = (pos_x - map_x) * delta_dist_x;
//         }
//         else
//         {
//             step_x = 1;
//             side_dist_x = (map_x + 1.0 - pos_x) * delta_dist_x;
//         }
//         if (ray_dir_y < 0)
//         {
//             step_y = -1;
//             side_dist_y = (pos_y - map_y) * delta_dist_y;
//         }
//         else
//         {
//             step_y = 1;
//             side_dist_y = (map_y + 1.0 - pos_y) * delta_dist_y;
//         }
//         // Ray casting loop
//         while (hit == 0)
//         {
//             // ... (ray casting logic)
//             if (side_dist_x < side_dist_y)
//             {
//                 side_dist_x += delta_dist_x;
//                 map_x += step_x;
//                 side = 0;
//             }
//             else
//             {
//                 side_dist_y += delta_dist_y;
//                 map_y += step_y;
//                 side = 1;
//             }
//             // Detect collision with wall
//             if (cub3d->config->map[map_y][map_x] > 0 && cub3d->config->map[map_y][map_x] < 2)
//                 hit = 1;
//         }





//         //after detecting collisions with the walls in the map, we calculate the distance to
//         //the wall and determining the height to render the wall on the screen        
//         /* Calculating Perpendicular Wall Distance:
//             The code determines whether the ray hit a vertical (side == 0) or horizontal (side == 1) wall. This is important for wall rendering.
//             The variable perp_wall_dist represents the perpendicular distance from the player's position to the wall. It's calculated based on the side where the ray hit.
//             If the ray hits a vertical wall (side == 0), it calculates perp_wall_dist using the difference between side_dist_x and delta_dist_x. Similarly, if it hits a horizontal wall, it uses side_dist_y and delta_dist_y. */
//         if (side == 0)
//             perp_wall_dist = (side_dist_x - delta_dist_x);
//         else
//             perp_wall_dist = (side_dist_y - delta_dist_y);
//         /* Determining Line Height for Wall Rendering:
//             line_height is calculated as the height of the wall on the screen. It's inversely proportional to perp_wall_dist. Closer walls appear taller, while farther walls appear shorter.
//             draw_start and draw_end define the range of the wall's height to be rendered on the screen. These values specify where the wall starts and ends vertically on the screen. */

// double wall_height = SCREEN_HEIGTH / perp_wall_dist;

// // Apply perspective correction for wall heights
// // This could involve additional factors like distance, fov (field of view), etc.
// // Experiment with different formulas for better perspective correction
// wall_height *= cos(fabs(camera_x)); // Applying a simple correction factor

// int line_height = (int)wall_height;

//         // int line_height = (int)(SCREEN_HEIGTH / perp_wall_dist);
//         /* Adjusting Render Limits:
//             The code ensures that draw_start and draw_end values fit within the screen's height (SCREEN_HEIGTH). If draw_start is negative (outside the screen), it's adjusted to start at the top of the screen (0). Similarly, if draw_end exceeds the screen's height, it's adjusted to the screen's bottom boundary.
//             After these calculations, the code continues to the texture mapping and rendering phase, using the calculated values (draw_start, draw_end, etc.) to render the wall texture within the specified screen area corresponding to the detected wall.
//         */
//         int draw_start = (-line_height / 2) + (SCREEN_HEIGTH / 2);
//         if (draw_start < 0)
//             draw_start = 0;
//         int draw_end = (line_height / 2) + (SCREEN_HEIGTH / 2);
//         if (draw_end >= SCREEN_HEIGTH)
//             draw_end = SCREEN_HEIGTH - 1;
        
//         // Calculate texture mapping
//         double wall_x;
//         if (side == 0)
//             wall_x = pos_y + perp_wall_dist * ray_dir_y;
//         else
//             wall_x = pos_x + perp_wall_dist * ray_dir_x;
//         wall_x -= floor(wall_x);
//         int tex_x = (int)(wall_x * (double)cub3d->xpm.tex_width);
//         if (side == 0 && ray_dir_x > 0)
//             tex_x = cub3d->xpm.tex_width - tex_x - 1;
//         if (side == 1 && ray_dir_y < 0)
//             tex_x = cub3d->xpm.tex_width - tex_x - 1;
//         // Render the textured line on the screen
//         double step = 1.0 * cub3d->xpm.tex_height / line_height;
//         double tex_pos = (draw_start - SCREEN_HEIGTH / 2 + line_height / 2) * step;
//         if (side == 1 && ray_dir_y > 0)
//             render_texture_line(draw_start, draw_end, x, tex_pos, step, cub3d, cub3d->xpm.s_tex_adrr, tex_x);
//         else if (side == 1 && ray_dir_y < 0)
//             render_texture_line(draw_start, draw_end, x, tex_pos, step, cub3d, cub3d->xpm.n_tex_adrr, tex_x);
//         else if (side == 0 && ray_dir_x > 0)
//             render_texture_line(draw_start, draw_end, x, tex_pos, step, cub3d, cub3d->xpm.e_tex_adrr, tex_x);
//         else
//             render_texture_line(draw_start, draw_end, x, tex_pos, step, cub3d, cub3d->xpm.w_tex_adrr, tex_x);
//         // Update 'x' to proceed to the next column
//     }
// }


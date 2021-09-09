/*
 * Author: Pedro José Pérez García
 * Date: 20/07/2021
 * Coms: Tipo de dato que va a representar una imagen + funciones para tratarla
 */

#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "Vector3.h"
#include "../Misc/CommonDefines.h"
using namespace std;

struct Image
{
	std::vector<Color> pixels;
	int height, width;
	//For Reinhard tone mapping
	float r_max, g_max, b_max, l_max;
	float log_avg_r, log_avg_g, log_avg_b, log_avg_l;
	float max = 0.0f;
	float c;

    void save_output(string name, string extension) {
        int r, g, b;
        ofstream out;
        out.open(name + "." + extension);
        if (extension == "ppm") {// ppm (LDR)
            out << "P3\n";
            out << width << " " << height << "\n";
            out << (int)c << "\n";
            for (int i = 0; i < height; i++) {
                for (int j = 0; j < width; j++) {
                    r = (int)(pixels[i * width + j].r * c); //+ 0.5
                    g = (int)(pixels[i * width + j].g * c);
                    b = (int)(pixels[i * width + j].b * c);
                    out << r << " " << g << " " << b;
                    if (j == width - 1) {
                        out << "\n";
                    }
                    else {
                        out << "\t";
                    }
                }
            }
        }
        out.close();
    }

	void tone_map(string method)
	{
        cout << "Tone mapping the image..." << endl;
        if (method.compare("clamp") == 0) {
            for (int i = 0; i < height * width; i++) {
                pixels[i].clamp(1.0);
            }
        }
        else if (method.compare("eq") == 0) {
            for (int i = 0; i < height * width; i++) {
                pixels[i].equalize(1.0);
            }
        }
        else if (method.compare("eq_clamp") == 0) {
            for (int i = 0; i < height * width; i++) {
                pixels[i].equalize_and_clamp(max * 0.9f);
            }
        }
        else if (method.compare("gamma") == 0) {
            for (int i = 0; i < height * width; i++) {
                pixels[i].gamma_curve(max, 2.22);
            }
        }
        else if (method.compare("clamp_gamma") == 0) {
            for (int i = 0; i < height * width; i++) {
                pixels[i].clamp_and_gamma_curve(max * 0.9, 2.22);
            }
        }
        else if (method.compare("reinhard_g") == 0) {
            for (int i = 0; i < height * width; i++) {
                pixels[i].reinhard_global(log_avg_r, log_avg_g, log_avg_b, max, 0.18);
                pixels[i].clamp(1.0);
            }
        }
        else if (method.compare("reinhard_g_pt") == 0) {
            float lwhite = RGBtoXYZ(Color{max, max, max}).g;
            cout << "l_max / lwhite: " << (float)l_max / (float)lwhite << endl;
            cout << "L_MAX: " << l_max << endl;
            Color aux;
            for (int i = 0; i < height * width; i++) {
                aux = RGBtoXYZ(pixels.at(i));
                float Y_ = aux.reinhard_global(log_avg_l, l_max, _REINHARD_a); //(float)min(1.0f, (float)l_max / (float)lwhite) * 0.95f
                aux = XYZtoYxy(aux);
                aux.r = Y_ * 100.0f;
                aux = XYZtoRGB(YxytoXYZ(aux));
                aux.clamp(1.0f);
                pixels.at(i) = aux;
            }
        }
        //Grzegorz Krawczyk, Karol Myszkowski, Hans-Peter Seidel, "Perceptual Effects in Real-time Tone Mapping", 2005
        else if (method.compare("reinhard_g_auto") == 0) {
            float lwhite = XYZtoYxy(RGBtoXYZ(Color{ 1.0f, 1.0f, 1.0f })).r;
            float a = 1.03 - (2 / (2 + (log10(log_avg_l + 1))));
            cout << "a_auto: " << a << endl;
            Color aux;
            for (int i = 0; i < height * width; i++) {
                aux = XYZtoYxy(RGBtoXYZ(pixels.at(i)));
                aux.reinhard_global(log_avg_l, (float)min(1.0f, (float)l_max / (float)lwhite) * 0.9f, a);
                aux = XYZtoRGB(YxytoXYZ(aux));
                aux.clamp(1.0);
                pixels.at(i) = aux;
            }
        }
        else {
            cerr << "ERROR: Tone mapping operator " << method << " not found!" << endl;
        }
	}

    void initialize_from_vector() {
        float l;
        float l_acum = 0;
        unsigned long int n_pixels = 0;       //Numero de pixeles tenidos en cuenta, ignoro los que son 100% negros
        c = powf(2.0f, 15.0f);
        l_max = 0;
        Color px;
        for (Color p : pixels)
        {
            //ignorar puntos negros
            if (max_px(p) != 0.0f)
            {
                if (max_px(p) > max)
                {
                    max = max_px(p);
                }
                px = RGBtoXYZ(p);
                l = px.g; //La segunda componente del pixel en XYZ es la luminancia
                if (l > l_max) { l_max = l; }
                l_acum = l_acum + (float)logf(((float)_REINHARD_DELTA + l));
                //cout << "l_acum " << n_pixels << ": " << l_acum << endl;
                n_pixels++;
            }
        }
        log_avg_l = expf(l_acum / (float)n_pixels);
        cout << log_avg_l << endl;
        //cout << expf(l_acum) << " " << (float)pixels.size() << endl;
    }

};

string read_line(ifstream& in);
//TODO harán falta más cosas?
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 11:44:23 by chaueur           #+#    #+#             */
/*   Updated: 2018/05/10 12:32:49 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "clmanager.h"
#include "particlemanager.h"
#include "window.h"

int main(void)
{
    Window *win = new Window();
    ParticleManager *particleManager = new ParticleManager();
    win->loadShaders();
    particleManager->setAttributes(win->shaderProgram);
    CLManager *clManager = new CLManager();
    clManager->initCL();
    clManager->setShape(win->initShape);
    clManager->computeMemory(particleManager->getPosVBO());
    clManager->runInitKernel();
    win->render(*clManager, *particleManager);
    return (1);
    // ParticleSysWindow window;
    // window.resize(1280, 1050);
    // window.show();

    // return app.exec();
}

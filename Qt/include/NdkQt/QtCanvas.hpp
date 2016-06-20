// Copyright (C) 2016 Jérôme Leclercq
// This file is part of the "Nazara Development Kit Qt Layer"
// For conditions of distribution and use, see copyright notice in Prerequesites.hpp

#pragma once

#ifndef NDK_QT_CANVAS_HPP
#define NDK_QT_CANVAS_HPP

#include <NdkQt/Prerequesites.hpp>
#include <Nazara/Renderer/RenderWindow.hpp>
#include <QtWidgets/QWidget>

namespace Ndk
{
	class NDK_QT_API QtCanvas : public QWidget, public Nz::RenderWindow
	{
		public:
			QtCanvas(QWidget* parent);

			unsigned int GetHeight() const;
			unsigned int GetWidth() const;

			virtual QSize minimumSizeHint() const override;
			virtual QSize sizeHint() const override;

		private:
			void paintEvent(QPaintEvent*) override;
			QPaintEngine* paintEngine() const override;
			
			void resizeEvent(QResizeEvent*) override;

			void showEvent(QShowEvent*) override;

			virtual void keyPressEvent(QKeyEvent* key) override;
	};
}

#include <NdkQt/QtCanvas.inl>

#endif // NDK_QT_CANVAS_HPP

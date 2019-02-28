//
// SVisual Project
// Copyright (C) 2018 by Contributors <https://github.com/Tyill/SVisual>
//
// This code is licensed under the MIT License.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files(the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions :
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//
#pragma once

#include "src/stdafx.h"
#include "SVConfig/SVConfigData.h"
#include "SVGraphPanel/SVGraphPanel.h"
#include "src/wdgAxisTime.h"
#include "src/wdgAxisValue.h"
#include "src/wdgMarker.h"
#include "SVGraphPanel/forms/ui_wdgGraph.h"
#include "SVGraphPanel/forms/graphPanel.h"

class wdgGraph : public QWidget
{
	Q_OBJECT

private:
	
	struct graphSignData{
		QString sign;
		QString name;
		SV_Cng::valueType type;
		int num;
		QColor color;
		QLabel* lb;
		QLabel* lbLeftMarkVal;
		QLabel* lbRightMarkVal;
		std::vector<std::vector<std::pair<int, int>>> pnts;
	};

	struct histPos{
		std::pair<double, double> valIntl;
		std::pair<qint64, qint64> tmIntl;
	};

	QImage imSign_;

	bool repaintEna_ = false,
        selLeftMark_ = false, selRigthMark_ = false;

	int colorCnt_ = 0;
		
	QMap <QString, graphSignData> signals_, signalsAlter_;
	QStringList signalList_, signalListAlter_;
		
	std::vector<std::vector<std::pair<int, int>>> getSignalPnt(SV_Cng::signalData* sign, bool isAlter = false);
	std::pair<double, double > getSignMaxMinValue(graphSignData* sign);
	std::pair<double, double> getSignMaxMinValue(SV_Cng::signalData* sign, std::pair<qint64, qint64>& tmInterval);
	void addPosToHistory();

	wdgAxisTime* axisTime_ = NULL;
	
	wdgMarker* leftMarker_ = NULL;
	wdgMarker* rightMarker_ = NULL;
	
	bool eventFilter(QObject *target, QEvent *event);

	std::vector<histPos> historyPos_;
	graphPanel* grPanel_ = nullptr;
    SV_Graph::config cng;

    void paintSignals();
	void paintSignalsAlter();
	void paintObjects();
	void paintObjectsAlter();
	
public:
	Ui::wdgGraphClass ui;

	struct graphSignPoint{
		int xPix, yPix;
		double val;
		QString sign;
		QString name;
		SV_Cng::valueType type;
		QColor color;
	};


	wdgGraph(QWidget *parent, SV_Graph::config cng_);
	~wdgGraph();
	
	QPainter plotPainterMem_;

	void setAxisTime(wdgAxisTime* axisTime);
	void plotUpdate();
	
	void setMarkersPos(QPoint left, QPoint right);
	void getMarkersPos(QPoint& left, QPoint& right);
	std::vector<graphSignPoint> getSignalValueByMarkerPos(int pos);
	std::vector<wdgGraph::graphSignPoint> getSignalAlterValueByMarkerPos(int pos);
	void addSignal(QString sign);
	void addAlterSignal(QString sign);
	QStringList getAllSignals();
	QStringList getAllAlterSignals();
	QSize sizeHint();
	void scale(bool posNeg);   

protected:
	void dragEnterEvent(QDragEnterEvent *event);
	void dragMoveEvent(QDragMoveEvent *event);
	void dropEvent(QDropEvent *event);
	void resizeEvent(QResizeEvent * event);

public slots:
	void axisValueChange();
	void axisTimeChange();
	void delSignal(QString sign, bool isLabelSender = true);
	void delSignalAlter(QString sign, bool isLabelSender = true);
	void resizeByTime();
	void resizeByValue();
	void resizeByRect();
	void showMarkPos();
	void updateByMarker();
	void undoCmd();
	void colorUpdate();

signals:
	void req_axisTimeUpdate(QString name);
	void req_markerChange(QString name);
	void req_selectGraph(QString name);
	void req_graphUp(QString name);
	void req_graphDn(QString name);
	void req_close();
};

/**
 * Form Factor & Scattering Length Dialog
 * @author Tobias Weber <tobias.weber@tum.de>
 * @date nov-2015
 * @license GPLv2
 */

#ifndef __TAKIN_FF_DLG_H__
#define __TAKIN_FF_DLG_H__

#include <QDialog>
#include <QSettings>

#include <vector>
#include <memory>

#include "ui/ui_formfactors.h"

#include "libs/qthelper.h"
#include "libs/qwthelper.h"
#include "libs/globals.h"


class FormfactorDlg : public QDialog, Ui::FormFactorDlg
{ Q_OBJECT
private:
	QListWidgetItem *m_pCurAtom = nullptr;
	QListWidgetItem *m_pCurMagAtom = nullptr;


protected:
	QSettings *m_pSettings = nullptr;

	// form factors
	std::vector<t_real_glob> m_vecQ, m_vecFF;
	std::unique_ptr<QwtPlotWrapper> m_plotwrap;

	// mag form factors
	std::vector<t_real_glob> m_vecQ_m, m_vecFF_m;
	std::unique_ptr<QwtPlotWrapper> m_plotwrap_m;

	// scattering lengths
	std::vector<t_real_glob> m_vecElem, m_vecSc;
	std::unique_ptr<QwtPlotWrapper> m_plotwrapSc;


protected:
	virtual void closeEvent(QCloseEvent* pEvt) override;
	virtual void accept() override;

	void SetupAtoms();
	void SetupMagAtoms();

	t_real_glob GetFormFact(t_real_glob dQ) const;
	t_real_glob GetMagFormFact(t_real_glob dQ) const;

protected slots:
	void SearchAtom(const QString& qstr);
	void AtomSelected(QListWidgetItem *pItem, QListWidgetItem *pItemPrev);

	void SearchMagAtom(const QString& qstr);
	void MagAtomSelected(QListWidgetItem *pItem, QListWidgetItem *pItemPrev);
	void RefreshMagAtom();
	void CalcTermSymbol(const QString& qstr);
	void Calcg();

	void SearchSLAtom(const QString& qstr);
	void PlotScatteringLengths();
	void SetupScatteringLengths();

	void cursorMoved(const QPointF& pt);

public:
	FormfactorDlg(QWidget* pParent = nullptr, QSettings *pSettings = nullptr);
	virtual ~FormfactorDlg();
};

#endif

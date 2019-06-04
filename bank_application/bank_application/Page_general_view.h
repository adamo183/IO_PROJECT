#pragma once
#include "Page.h"


class Page_general_view :
	public Page
{
public slots:
	void send_transfer();
	void show_acc_over();
public:
	void showPage() override;
	void setHidden(bool emitSignal = true) override;

	Page_general_view(QScrollArea * parent = Q_NULLPTR, DB_Holder * db = nullptr, const QString & CSS = "" , account *user = Q_NULLPTR) : Page(parent, CSS), db_holder(db) , User(user) {};
	~Page_general_view();
	   

private:

	DB_Holder * db_holder = nullptr;

	QLabel * lbl = Q_NULLPTR;
	account* User = Q_NULLPTR;

	QWidget * layout_widget = Q_NULLPTR;
	QWidget* topWigdet = Q_NULLPTR;
	QHBoxLayout* top_bar = Q_NULLPTR;
	QPushButton* menu_bton = Q_NULLPTR;
	QPushButton* out_bton = Q_NULLPTR;
	QLabel * acc_lab = Q_NULLPTR;
	QLabel* curr_lab = Q_NULLPTR;
	QVBoxLayout* acc_bar = Q_NULLPTR;
	QHBoxLayout* box_layout = Q_NULLPTR;
	QGridLayout* data_lay = Q_NULLPTR;
	QGroupBox* acc_frame = Q_NULLPTR;
	QLabel* money = Q_NULLPTR;
	QLabel* trans_name_1 = Q_NULLPTR;
	QLabel* trans_value_1 = Q_NULLPTR;
	QLabel* trans_name_2 = Q_NULLPTR;
	QLabel* trans_value_2 = Q_NULLPTR;
	QPushButton*  acc_view = Q_NULLPTR;
	QGroupBox* quick_wid = Q_NULLPTR;
	QLabel* quick_lab = Q_NULLPTR;
	QGridLayout * quick_grid = Q_NULLPTR;
	QLabel* iwant_transf = Q_NULLPTR;
	QLabel* from = Q_NULLPTR;
	QLabel* to = Q_NULLPTR;
	QPushButton* showMore = Q_NULLPTR;
	QPushButton* send = Q_NULLPTR;
	QLineEdit* transf_field = Q_NULLPTR;
	QLineEdit* title_field = Q_NULLPTR;
	QLineEdit* to_field = Q_NULLPTR;



};

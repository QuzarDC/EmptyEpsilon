#include <i18n.h>
#include "playerInfo.h"
#include "selfDestructEntry.h"
#include "components/selfdestruct.h"

#include "gui/gui2_panel.h"
#include "gui/gui2_label.h"
#include "gui/gui2_button.h"

GuiSelfDestructEntry::GuiSelfDestructEntry(GuiContainer* owner, string id)
: GuiElement(owner, id)
{
    setSize(GuiElement::GuiSizeMax, GuiElement::GuiSizeMax);

    box = new GuiPanel(this, id + "_BOX");
    box->setPosition(0, 0, sp::Alignment::Center)->setAttribute("layout", "vertical");;
    (new GuiLabel(box, id + "_LABEL", tr("Self destruct activated!"), 50))->setSize(600, 80)->layout.alignment = sp::Alignment::Center;
    code_label = new GuiLabel(box, id + "_CODE_LABEL", "", 30);
    code_label->addBackground()->setSize(GuiElement::GuiSizeMax, 50)->layout.alignment = sp::Alignment::Center;

    code_entry = new GuiElement(box, id + "_ENTRY_ELEMENT");
    code_entry->setSize(250, 320)->setPosition(0, 0, sp::Alignment::Center);

    code_entry_code_label = new GuiLabel(code_entry, id + "_ENTRY_LABEL", "Enter [A]", 30);
    code_entry_code_label->addBackground()->setSize(GuiElement::GuiSizeMax, 50);
    code_entry_label = new GuiLabel(code_entry, id + "_ENTRY_LABEL", "", 30);
    code_entry_label->addBackground()->setPosition(0, 50, sp::Alignment::TopLeft)->setSize(GuiElement::GuiSizeMax, 50);
    (new GuiButton(code_entry, id + "_BUTTON_7", "7", [this]() {code_entry_label->setText(code_entry_label->getText() + "7");}))->setSize(50, 50)->setPosition(50, 100, sp::Alignment::TopLeft);
    (new GuiButton(code_entry, id + "_BUTTON_8", "8", [this]() {code_entry_label->setText(code_entry_label->getText() + "8");}))->setSize(50, 50)->setPosition(100, 100, sp::Alignment::TopLeft);
    (new GuiButton(code_entry, id + "_BUTTON_9", "9", [this]() {code_entry_label->setText(code_entry_label->getText() + "9");}))->setSize(50, 50)->setPosition(150, 100, sp::Alignment::TopLeft);
    (new GuiButton(code_entry, id + "_BUTTON_4", "4", [this]() {code_entry_label->setText(code_entry_label->getText() + "4");}))->setSize(50, 50)->setPosition(50, 150, sp::Alignment::TopLeft);
    (new GuiButton(code_entry, id + "_BUTTON_5", "5", [this]() {code_entry_label->setText(code_entry_label->getText() + "5");}))->setSize(50, 50)->setPosition(100, 150, sp::Alignment::TopLeft);
    (new GuiButton(code_entry, id + "_BUTTON_6", "6", [this]() {code_entry_label->setText(code_entry_label->getText() + "6");}))->setSize(50, 50)->setPosition(150, 150, sp::Alignment::TopLeft);
    (new GuiButton(code_entry, id + "_BUTTON_1", "1", [this]() {code_entry_label->setText(code_entry_label->getText() + "1");}))->setSize(50, 50)->setPosition(50, 200, sp::Alignment::TopLeft);
    (new GuiButton(code_entry, id + "_BUTTON_2", "2", [this]() {code_entry_label->setText(code_entry_label->getText() + "2");}))->setSize(50, 50)->setPosition(100, 200, sp::Alignment::TopLeft);
    (new GuiButton(code_entry, id + "_BUTTON_3", "3", [this]() {code_entry_label->setText(code_entry_label->getText() + "3");}))->setSize(50, 50)->setPosition(150, 200, sp::Alignment::TopLeft);
    (new GuiButton(code_entry, id + "_BUTTON_Clr", "Clr", [this]() {code_entry_label->setText("");}))->setSize(50, 50)->setPosition(50, 250, sp::Alignment::TopLeft);
    (new GuiButton(code_entry, id + "_BUTTON_0", "0", [this]() {code_entry_label->setText(code_entry_label->getText() + "0");}))->setSize(50, 50)->setPosition(100, 250, sp::Alignment::TopLeft);
    (new GuiButton(code_entry, id + "_BUTTON_OK", "OK", [this]() {
        if (my_spaceship)
            my_player_info->commandConfirmDestructCode(code_entry_position, code_entry_label->getText().toInt());
        code_entry_label->setText("");
    }))->setSize(50, 50)->setPosition(150, 250, sp::Alignment::TopLeft);
}

void GuiSelfDestructEntry::onDraw(sp::RenderTarget& target)
{
    if (my_spaceship)
    {
        auto self_destruct = my_spaceship.getComponent<SelfDestruct>();
        if (self_destruct && self_destruct->active)
        {
            box->show();
            string codes = "";
            int lines = 0;
            code_entry_position = -1;
            for(int n=0; n<SelfDestruct::max_codes; n++)
            {
                if (has_position.has(self_destruct->show_position[n]))
                {
                    if (lines > 0)
                        codes = codes + "\n";
                    codes = codes + tr("Code [{letter}]: {self_destruct_code}").format({{"letter", string(char('A' + n))}, {"self_destruct_code", string(self_destruct->code[n])}});

                    lines++;
                }
                if (has_position.has(self_destruct->entry_position[n]) && !self_destruct->confirmed[n] && code_entry_position < 0)
                {
                    code_entry_position = n;
                }
            }
            code_label->setSize(GuiElement::GuiSizeMax, 30 + 30 * lines);
            code_label->setText(codes);
            code_label->setVisible(lines > 0);

            code_entry_code_label->setText(tr("selfdestruct", "Enter [{letter}]").format({{"letter", string(char('A' + code_entry_position))}}));

            code_entry->setVisible(code_entry_position > -1);
        }else{
            box->hide();
        }
    }else{
        box->hide();
    }
}

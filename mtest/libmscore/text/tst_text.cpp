//=============================================================================
//  MuseScore
//  Music Composition & Notation
//  $Id:$
//
//  Copyright (C) 2012 Werner Schweer
//
//  This program is free software; you can redistribute it and/or modify
//  it under the terms of the GNU General Public License version 2
//  as published by the Free Software Foundation and appearing in
//  the file LICENCE.GPL
//=============================================================================

#include <QtTest/QtTest>

#include "libmscore/text.h"
#include "libmscore/score.h"
#include "libmscore/sym.h"
#include "mtest/testutils.h"

using namespace Ms;

//---------------------------------------------------------
//   TestNote
//---------------------------------------------------------

class TestText : public QObject, public MTest
      {
      Q_OBJECT

   private slots:
      void initTestCase();
      void testText();
      };

//---------------------------------------------------------
//   initTestCase
//---------------------------------------------------------

void TestText::initTestCase()
      {
      initMTest();
      }

//---------------------------------------------------------
///   testText
///   read/write test of note
//---------------------------------------------------------

void TestText::testText()
      {
      Text* text = new Text(score);
      text->setTextStyle(score->textStyle(TEXT_STYLE_DYNAMICS));

      text->setEditMode(true);
      text->layout();

      text->moveCursorToEnd();
      text->insertText("a");
      text->endEdit();
      QCOMPARE(text->text(), QString("a"));

      text->setEditMode(true);
      text->moveCursorToEnd();
      text->insertText("bc");
      text->endEdit();
      QCOMPARE(text->text(), QString("abc"));

      text->setEditMode(true);
      text->moveCursorToEnd();
      text->insertText("d");
      text->insertText("e");
      text->endEdit();
      QCOMPARE(text->text(), QString("abcde"));

      text->setEditMode(true);
      text->moveCursorToStart();
      text->insertText("1");
      text->endEdit();
      QCOMPARE(text->text(), QString("1abcde"));

      text->setEditMode(true);
      text->moveCursorToStart();
      text->insertText("0");
      text->endEdit();
      QCOMPARE(text->text(), QString("01abcde"));

      text->setEditMode(true);
      text->moveCursorToStart();
      text->movePosition(QTextCursor::Right);
      text->movePosition(QTextCursor::Right);
      text->insertText("2");
      text->endEdit();
      QCOMPARE(text->text(), QString("012abcde"));

      text->setEditMode(true);
      text->moveCursorToEnd();
      text->movePosition(QTextCursor::Left);
      text->movePosition(QTextCursor::Left);
      text->movePosition(QTextCursor::Left);
      text->movePosition(QTextCursor::Left);
      text->movePosition(QTextCursor::Left);
      text->insertText("3");
      text->endEdit();
      QCOMPARE(text->text(), QString("0123abcde"));

      text->setEditMode(true);
      text->moveCursorToEnd();
      text->insertSym(SymId::segno);
      text->endEdit();
      QCOMPARE(text->text(), QString("0123abcde<sym>segno</sym>"));

      text->setEditMode(true);
      text->movePosition(QTextCursor::Left);
      text->insertText("#");
      text->endEdit();
      QCOMPARE(text->text(), QString("0123abcde#<sym>segno</sym>"));
      }

QTEST_MAIN(TestText)

#include "tst_text.moc"


// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_VIEWS_FRAME_TEST_WITH_BROWSER_VIEW_H_
#define CHROME_BROWSER_UI_VIEWS_FRAME_TEST_WITH_BROWSER_VIEW_H_

#include <memory>

#include "base/macros.h"
#include "chrome/test/base/browser_with_test_window_test.h"
#include "chrome/test/views/scoped_macviews_browser_mode.h"

class BrowserView;

// Base class for BrowserView based unit tests. TestWithBrowserView creates
// a Browser with a valid BrowserView and BrowserFrame with as little else as
// possible.
class TestWithBrowserView : public BrowserWithTestWindowTest {
 public:
  TestWithBrowserView();
  TestWithBrowserView(Browser::Type browser_type, bool hosted_app);
  ~TestWithBrowserView() override;

  // BrowserWithTestWindowTest overrides:
  void SetUp() override;
  void TearDown() override;
  TestingProfile* CreateProfile() override;
  BrowserWindow* CreateBrowserWindow() override;

  BrowserView* browser_view() { return browser_view_; }

 private:
  BrowserView* browser_view_;  // Not owned.
  test::ScopedMacViewsBrowserMode views_mode_{true};

  DISALLOW_COPY_AND_ASSIGN(TestWithBrowserView);
};

#endif  // CHROME_BROWSER_UI_VIEWS_FRAME_TEST_WITH_BROWSER_VIEW_H_

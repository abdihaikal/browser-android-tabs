// Copyright 2018 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "content/browser/download/url_downloader_factory.h"

#include "components/download/public/common/download_item.h"
#include "content/browser/download/download_request_core.h"
#include "content/browser/download/url_downloader.h"

namespace content {

UrlDownloaderFactory::UrlDownloaderFactory() = default;

UrlDownloaderFactory::~UrlDownloaderFactory() = default;

download::UrlDownloadHandler::UniqueUrlDownloadHandlerPtr
UrlDownloaderFactory::CreateUrlDownloadHandler(
    std::unique_ptr<download::DownloadUrlParameters> params,
    base::WeakPtr<download::UrlDownloadHandler::Delegate> delegate,
    scoped_refptr<network::SharedURLLoaderFactory> shared_url_loader_factory,
    const scoped_refptr<base::SingleThreadTaskRunner>& task_runner) {
  std::unique_ptr<net::URLRequest> url_request =
      DownloadRequestCore::CreateRequestOnIOThread(
          download::DownloadItem::kInvalidId, params.get());

  return download::UrlDownloadHandler::UniqueUrlDownloadHandlerPtr(
      UrlDownloader::BeginDownload(delegate, std::move(url_request),
                                   params.get(), true)
          .release(),
      base::OnTaskRunnerDeleter(base::ThreadTaskRunnerHandle::Get()));
}

}  // namespace content
